import sys
import os
from pathlib import Path
from bs4 import BeautifulSoup
import requests
import re
from urllib.request import Request, urlopen
from urllib.error import HTTPError, URLError

import cloudscraper

HEADERS = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}

def delete_files(problem_name):
    current_dir = Path(__file__).parent
    tests = current_dir / "tests"   

    files = sorted(tests.glob(f"{problem_name}-*.in"))

    for file in files:
        test_name = file.stem
        os.remove(f"tests/{str(test_name)}.in")
        os.remove(f"tests/{str(test_name)}.ans")
        #print(f"tests/{str(test_name)}.in deleted")
        #print(f"tests/{str(test_name)}.ans deleted")

def create_file(name, text):
    with open(name, "w") as f:
        f.write(text)

def get_html(url):

    scraper = cloudscraper.create_scraper()
    response = scraper.get(url)

    print(f"Status Code {response.status_code}")
    return response.text

def codeforces_parse_class(soup):
    pre = soup.find("pre")
    lines = pre.find_all("div", class_="test-example-line") if pre else []
    text = (
        "\n".join(line.get_text().strip().replace("\xa0", " ") for line in lines)
        if lines
        else "\n".join(pre.stripped_strings).replace("\xa0", " ")
        if pre
        else ""
    )
    return text


def create_codeforces(problem_name, html):
    soup = BeautifulSoup(html, 'html.parser')

    sample_test = soup.find("div", class_="sample-test")

    inputs = soup.find_all('div', class_='input')
    answers = soup.find_all('div', class_='output')

    for sample_nb, (inp, ans) in enumerate(zip(inputs, answers), 1):

        file_name = "tests/" + problem_name + "-" + str(sample_nb)
        
        # Extract input & answer
        input_text = codeforces_parse_class(inp)
        answer_text = codeforces_parse_class(ans)

        os.makedirs("tests", exist_ok=True)

        create_file(file_name + ".in", input_text)
        create_file(file_name + ".ans", answer_text)
        print(file_name + " created")


def create_atcoder(problem_name, html):

    soup = BeautifulSoup(html, 'html.parser')

    for sample_nb in range(1, 100):
        input_name = f"Sample Input {sample_nb}"

        h3 = soup.find("h3", string=input_name)

        if h3 is None:
            break

        sample = h3.find_next("pre")
        input_text = sample.get_text(" ", strip=True)

        answer_name = f"Sample Output {sample_nb}"
        h3 = soup.find("h3", string=answer_name)

        sample = h3.find_next("pre")
        answer_text = sample.get_text(" ", strip=True)

        os.makedirs("tests", exist_ok=True)

        file_name = "tests/" + problem_name + "-" + str(sample_nb)

        create_file(file_name + ".in", input_text)
        create_file(file_name + ".ans", answer_text)
        print(file_name + " created")

def create(name, webiste, contest, problem):

    if website == "cf":
        url = f"https://codeforces.com/contest/{contest}/problem/{problem}"
    elif website == "ac":
        url = f"https://atcoder.jp/contests/{contest}/tasks/{contest}_{round}"
    else:
        print(f"{website} cannot be parsed")
        return

    html = get_html(url)

    if website == "cf":
        create_codeforces(name, html)
    elif website == 'ac':
        create_atcoder(name, html)
    else:
        print(f"{url} cannot be parsed")


if __name__ == "__main__":
    name = sys.argv[1]
    website = sys.argv[2]
    contest = sys.argv[3]
    problem = sys.argv[4]


    delete_files(name)    

    create(name, website, contest, problem)
