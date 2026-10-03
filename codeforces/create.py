import sys
import os
from pathlib import Path
from bs4 import BeautifulSoup
import requests
import re

def delete(problem_name):
	current_dir = Path(__file__).parent
	tests = current_dir / "tests"	

	files = sorted(tests.glob(f"{problem_name}-*.in"))

	for file in files:
		test_name = file.stem

		os.remove(f"tests/{str(test_name)}.in")
		os.remove(f"tests/{str(test_name)}.ans")

def get_html(url):
	response = requests.get(url)
	return response.text

def create_at_coder():
	pass

def create(problem_name, html):

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

	    file_name = "tests/" + problem_name + "-" + str(sample_nb)

	    with open(file_name + ".in", "w") as f:
	        f.write(input_text)

	    with open(file_name + ".ans", "w") as f:
	        f.write(answer_text)

	    print(file_name + " created")

if __name__ == "__main__":
	problem_name = sys.argv[1]
	url = sys.argv[2]

	delete(problem_name)

	html = get_html(url)	

	create(problem_name, html)











