"""
PyLatin Rules ->
  1.) If the word has non-alphabetic letter then return ValueError
  2.) If the word is under 3 characters, return the word how it was inputted
  3.) If the word begins with a PyLatin vowel, then 'on' is added to the end, followed by all leading vowels
  4.) If the word begins with a Consonant, 'py' is added to the end, followed by all leading consonants
"""

import re
import string


"""word_to_pylatin -> Converts a inputted word to PyLatin utilizing the PyLatin Rules (see top for rules)"""
def word_to_pylatin(word):
    # Non-Alphabet character check
    nonalpha_regex = re.compile(r'[^a-z]', re.IGNORECASE)
    nonalpha_check = nonalpha_regex.search(word)

    if nonalpha_check is not None:
        raise ValueError("word contains invalid character: " + nonalpha_check.group(0))

    # If word contains < 3 Characters, return it how it was inputted
    if len(word) < 3:
        return word

    # If word begins with a PyLatin vowel, then 'on' is added to the end, followed by all leading vowels
    vowel_beg_regex = re.compile(r'^([aeiouy]+)([bcdfghjklmnpqrstvwxz]*[a-z]*)$', re.IGNORECASE)
    vowel_beg_check = vowel_beg_regex.search(word)

    if vowel_beg_check is not None:
        beginning_of_string = vowel_beg_check.group(2)
        end_of_string = vowel_beg_check.group(1)

        return_string = beginning_of_string + "on" + end_of_string

        return return_string

    # If the word begins with a Consonant, 'py' is added to the end, followed by all leading consonants
    consonant_beg_regex = re.compile(r'^([bcdfghjklmnpqrstvwxz]+)([bcdfghjklmnpqrstvwxz]*[a-z]*)$', re.IGNORECASE)
    consonant_beg_check = consonant_beg_regex.search(word)

    if consonant_beg_check is not None:
        beginning_of_string = consonant_beg_check.group(2)
        end_of_string = consonant_beg_check.group(1)

        return_string = beginning_of_string + "py" + end_of_string

        return return_string


"""word_from_pylatin -> Converts a inputted PyLatin word to english utilizing the PyLatin Rules (see top for rules)"""
def word_from_pylatin(word):
    # Non-Alphabet character check
    nonalpha_regex = re.compile(r'[^a-z]', re.IGNORECASE)
    nonalpha_check = nonalpha_regex.search(word)

    if nonalpha_check is not None:
        raise ValueError("word contains invalid character: " + nonalpha_check.group(0))

    # If word contains < 3 Characters, return it how it was inputted
    if len(word) < 3:
        return word

    # If word begins with a consonant and ends with on followed by vowels, then remove the 'on' & move vowels to beg.
    consonant_beg_regex = re.compile(r'hahahah', re.IGNORECASE)
    consonant_beg_check = consonant_beg_regex.search(word)

    if consonant_beg_check is not None:
        end_of_string = consonant_beg_check.group(1)
        beginning_of_string = consonant_beg_check.group(2)


        return_string = beginning_of_string + end_of_string

        return return_string

    # If a word begins with a vowel and ends with py followed by cons., then remove the 'py' and move cons. to beg.
    vowel_beg_regex = re.compile(r'^([aeiouy][a-z]*|)py([bcdfghjklmnpqrstvwxz]*)$', re.IGNORECASE)
    vowel_beg_check = vowel_beg_regex.search(word)

    if vowel_beg_check is not None:
        end_of_string = vowel_beg_check.group(1)
        beginning_of_string = vowel_beg_check.group(2)

        return_string = beginning_of_string + end_of_string

        return return_string


"""convert_sentence -> Converts inputted sentence to specified language (PyLatin or English (to/from_pylatin))"""
def convert_sentence(sentence, conversion):
    # Checking if the conversion type was inputted correctly (either can be to_pylatin or from_pylatin)
    if conversion != "to_pylatin" and conversion != "from_pylatin":
        raise ValueError("You must select either 'to_pylatin' or 'from_pylatin' for conversion option.")

    # Split-up sentence/create return variable
    split_up_sentence = sentence.split()
    return_sentence = ""

    # Loop through split-up sentence, word-by-word
    for word in split_up_sentence:
        ascii_letters = string.ascii_letters

        # Check for Leading/Trailing Punctuation/Non-Ascii Letters (utilize string.ascii_letters for master list)
        lead_punc_regex = re.compile(r'^([^' + ascii_letters + ']+)([a-z]+)', re.IGNORECASE)
        lead_punc_check = lead_punc_regex.search(word)
        trail_punc_regex = re.compile(r'([a-z]+)([^' + ascii_letters + ']+)$', re.IGNORECASE)
        trail_punc_check = trail_punc_regex.search(word)

        if lead_punc_check is not None and trail_punc_check is not None:
            if conversion == "to_pylatin":
                updated_word_raw = word_to_pylatin(lead_punc_check.group(2))
            else:
                updated_word_raw = word_from_pylatin(lead_punc_check.group(2))

            updated_word_full = lead_punc_check.group(1) + updated_word_raw + trail_punc_check.group(2)
        elif lead_punc_check is not None and trail_punc_check is None:
            if conversion == "to_pylatin":
                updated_word_raw = word_to_pylatin(lead_punc_check.group(2))
            else:
                updated_word_raw = word_from_pylatin(lead_punc_check.group(2))

            updated_word_full = lead_punc_check.group(1) + updated_word_raw
        elif trail_punc_check is not None and lead_punc_check is None:
            if conversion == "to_pylatin":
                updated_word_raw = word_to_pylatin(trail_punc_check.group(1))
            else:
                updated_word_raw = word_from_pylatin(trail_punc_check.group(1))

            updated_word_full = updated_word_raw + trail_punc_check.group(2)
        else:
            if conversion == "to_pylatin":
                updated_word_full = word_to_pylatin(word)
            else:
                updated_word_full = word_from_pylatin(word)

        return_sentence += updated_word_full + " "

    # Remove last trailing whitespace character (" ")
    return return_sentence[0:len(return_sentence) - 1]


if __name__ == "__main__":
    sentence = 'axpyM ayspys, "unctuationpyp is to be gnoredoni..."'
    conversion = "from_pylatin"
    updated_sentence = convert_sentence(sentence, conversion)
    print("from_pylatin convert_sentence -> " + updated_sentence)

    word = word_to_pylatin("eye")
    print("word_to_pylatin -> " + word)

    word = word_from_pylatin("oneye")
    print("word_from_pylatin -> " + word)
