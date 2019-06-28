//Quiz Program
//Jack P.
//Description:  Reads a CSV File, which is formatted as [Question, Answer] each line.
//				Takes a timer flag and filename flag and asks the users questions till they are finished
//				or until they hit the time limit.

package main

import (
	"encoding/csv"
	"flag"
	"fmt"
	"os"
	"strings"
	"time"
)

//Problem Structure used for each line in CSV file ([question,answer] format)
type problem struct {
	question string
	answer string
}

//main function that runs the program
func main() {
	fileName := flag.String("QuizFileName", "Quiz.csv", "CSV File, Format -> 'question,answer'.")
	totalTime := flag.Int("TotalTime", 3, "Total time allowed for quiz.")
	flag.Parse()

	lines := openFileReadLines(*fileName)
	problemSlice := parseCsvLines(lines)

	//Quiz Begins -> Good luck
	correctAnswers := askQuestions(problemSlice, *totalTime)


	fmt.Printf("You scored %d out of %d.\n", correctAnswers, len(problemSlice))
}

//Exit Code 1 and print Message
func exit1(message string) {
	fmt.Println(message)
	os.Exit(1)
}

//Opens File and ReadAll File and then returns the 2D Slice String of the Lines
func openFileReadLines(fileName string) [][]string {
	file, err := os.Open(fileName)
	if err != nil {
		exit1(fmt.Sprintf("Encountered error: %s || File Name -> %s", err, fileName))
	}

	//Read All Lines from CSV, store in 'lines'
	reader := csv.NewReader(file)
	lines, err := reader.ReadAll()
	if err != nil {
		exit1(fmt.Sprintf("Encountered error reading CSV File -> %s", err))
	}

	return lines
}

//Parse the Lines from the CSV File
func parseCsvLines(lines [][]string) []problem {
	returnSlice := make([]problem, len(lines), len(lines))

	//Loop through CSV File Lines, for each question/answer trim all leading/trailing spaces
	for i, line := range lines {
		returnSlice[i] = problem {
			question: strings.TrimSpace(line[0]),
			answer: strings.TrimSpace(line[1]),
		}
	}

	return returnSlice
}

//Loop through the questions and ask for user input
//Utilizes GoRoutine when getting answer so that the
//timer does not stop/not stop quiz when the program is waiting for user input
func askQuestions(problemSlice []problem, totalTime int) int {
	var correctAnswers int

	//Timer is created and starts
	timer := time.NewTimer(time.Second * time.Duration(totalTime))

	//Loop through Problems and ask User for Answer, check answer validity
	for i, p := range problemSlice {
		fmt.Printf("Problem #%d: %s\n", i+1, p.question)

		//GoRoutine used so that user does not get unlimited time on current
		//question that they are on. It will kick them out if time runs out.
		answerChan := make(chan string)
		go func() {
			var answer string
			_, err := fmt.Scanf("%s", &answer)
			if err != nil {
				exit1("Error in receiving answer.")
			}

			answerChan <- answer
		}()

		//Checking to see if time is up / if answer is submitted and correct
		select {
		case <-timer.C:
			fmt.Println("You are out of time!")
			return correctAnswers
		case <-answerChan:
			answer := <-answerChan
			if answer == p.answer {
				correctAnswers++
			}
		}
	}

	return correctAnswers
}
