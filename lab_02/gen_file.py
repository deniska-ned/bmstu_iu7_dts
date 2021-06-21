import random

FILENAME = "database.txt"

ROW_COUNT = 140

TOURISM = [i for i in range(3)]
EXCURSION = [i for i in range(3)]
SEASON = [i for i in range(4)]
SPORT = [i for i in range(3)]
MAINLAND = [i for i in range(5)]

def gen_county_capital_list():
    data = []
    with open("countries.cvs", "r") as f:
        s = f.readline()

        i = 0
        while "" != s:
            s = f.readline()
            row = s.split(",")[:2]
            for i in range(len(row)):
                row[i] = row[i].replace('"', '')
                # row[i] = row[i].replace('\n', '')

            data.append(row)
    data.pop()

    return data

def is_char_alphabetic(char):
    if (ord(char) not in range(ord('a'), ord('z') + 1) and
            ord(char) not in range(ord('A'), ord('Z') + 1)):
        return False

    return True

def is_word_alhabetic(word):
    for char in word:
        if not is_char_alphabetic(char):
            return False

    return True

def process_data(data):
    new_data = []
    for country, capital in data:
        if is_word_alhabetic(country) and is_word_alhabetic(capital):
            new_data.append((country, capital))
    return new_data

def uint32_t():
    return str(random.randrange(2**32))

def int32_t():
    return str(random.randrange(-2**31, 2**31))

def main():
    country_capital = gen_county_capital_list()
    country_capital = process_data(country_capital)

    random.shuffle(country_capital)

    data = []

    print("Len:", min(len(country_capital), ROW_COUNT))
    for i in range(min(len(country_capital), ROW_COUNT)):
        row = ""

        el = country_capital.pop()
        row += (el[0].replace(" ", "_")[:10] + " " + uint32_t()  + " " +
                el[1].replace(" ", "_")[:10] + " " +
                str(random.choice(MAINLAND)))

        ch = random.choice(TOURISM)
        row += " " + str(ch) + " "

        if 0 == ch:
            row += (uint32_t()  +" "+
                    str(random.choice(EXCURSION)))
        elif 1 == ch:
            row += (str(random.choice(SEASON)) +" "+
                    int32_t()  +" "+
                    int32_t()  +" "+
                    uint32_t())
        elif 2 == ch:
            row += (str(random.choice(SPORT)) + " " +
                    uint32_t())
        else:
            assert(false)
        data.append(row)

    with open(FILENAME, "w") as f:
        for i in range(len(data)):
            f.write(data[i] + "\n")

if __name__ == "__main__":
    main()
