import sys
import os
import time
import filecmp
import resource
import cloudscraper

from pathlib import Path

GREEN = '\033[92m'
RED = '\033[91m'
END = '\033[0m'

DEBUG_FLAG = "debug"

def normalize(text):
	return ".".join(text.split())

def compile(program_name, problem_number, debug):

	if debug == DEBUG_FLAG or problem_number is not None:
		print(f"[DEBUG MODE] Compiling {program_name}.cpp with C++23")
		os.system(f"g++ -DDEBUG {program_name}.cpp -o {program_name}.out")
	else:
		print(f"Compiling {program_name}.cpp with C++23")
		os.system(f"g++ {program_name}.cpp -o {program_name}.out")

def check_solution(files):

	tests_total = 0
	tests_passed = 0

	for file in files:

		if file.stat().st_size == 0:
			continue

		test_name = file.stem

		print(f"Running {test_name}")

		input_name = test_name + ".in"
		output_name = test_name + ".out"
		answer_name = test_name + ".ans"

		start_time = time.time()
		os.system(f"./{program_name}.out < tests/{input_name} > tests/{output_name}")
		time_elapsed = time.time() - start_time
		usage = resource.getrusage(resource.RUSAGE_CHILDREN)

		print(f"Time: {time_elapsed:.3f}s")
		print(f"Memory: {usage.ru_maxrss / 1024:.2f} MB") # only for linux TODO for mac

		inp = Path(f"tests/{input_name}").read_text()
		out = Path(f"tests/{output_name}").read_text()
		exp = Path(f"tests/{answer_name}").read_text()

		same = normalize(out) == normalize(exp)

		print("---------------")
		print("Input:")
		print(inp)
		print("---------------")
		print("Output:")
		print(out)
		print("---------------")
		print("Expected:")
		print(exp)
		print("---------------")

		tests_total += 1
		if same:
			tests_passed += 1
			print(GREEN + "Passed!" + END + "\n")
		else:
			print(RED + "Failed!" + END + "\n")

		os.remove(f"tests/{output_name}")

	color = GREEN if (tests_passed == tests_total) else RED

	print(color + f"{tests_passed} / {tests_total} tests passed" + END + "\n")

	os.remove(f"{program_name}.out")

def run_custom_test():
	os.system(f"./{program_name}.out")
	os.remove(f"{program_name}.out")

def parse_arguments():
	program_name = sys.argv[1]
	problem_number = sys.argv[2] if len(sys.argv) > 2 else None
	debug = sys.argv[3] if len(sys.argv) > 3 else None

	return program_name, problem_number, debug

if __name__ == "__main__":

	program_name, problem_number, debug = parse_arguments()

	compile(program_name, problem_number, debug)

	if problem_number is not None and int(problem_number) == -1:
		run_custom_test()

	else:
		current_dir = Path(__file__).parent
		tests = current_dir / "tests"

		if problem_number is None:
			files = sorted(tests.glob(f"{program_name}-*.in"))
		else:
			files = (tests.glob(f"{program_name}-{problem_number}.in"))

		check_solution(files)


