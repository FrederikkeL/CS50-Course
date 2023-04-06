import cs50
text = cs50.get_string("Text: ")


def main():
    words = count_words(text)
    sentences = count_sentences(text)
    letters = count_letters(text)
    index = calculate_index(words, letters, sentences)
    # prints the correct grade level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    # counts letters
    letter = 0
    for i in range(len(text)):
        if text[i].isalpha() == True:
            letter += 1
    return letter


def count_words(text):
    # counts words by counting spaces
    word = 1
    for i in range(len(text)):
        if text[i] == " ":
            word += 1
    return word


def count_sentences(text):
    # counts sentences by counting . ? and !
    sentences = 0
    for i in range(len(text)):
        if text[i] == "!" or text[i] == "." or text[i] == "?":
            sentences += 1

    return sentences


def calculate_index(words, letters, sentences):
    # calculates index
    L = (letters / (words / 100.0))
    S = (sentences / (words / 100.0))
    index = round((0.0588 * L - 0.296 * S - 15.8))
    return index


if __name__ == "__main__":
    main()
