#!/bin/sh

# 1. Compile the program
make

test_dir="tests"
output_dir="outputs"

# 2. Get the current directory and wrap in quotes to handle spaces
current_dir="$(pwd)"

if [ -z "$current_dir" ]; then
  echo "No se pudo determinar el directorio actual"
  exit 1
fi

# Move to the project root
cd "$current_dir"

# 3. Prepare the output directory
mkdir -p "$output_dir"

# 4. Iterate through program folders (e.g., magnemites)
for program_path in "$test_dir"/*; do
    # Skip if it's not a directory
    [ -d "$program_path" ] || continue
    
    # Extract the name (e.g., 'magnemites')
    program=$(basename "$program_path")

    # Check if the executable exists in the current folder
    if [ ! -f "./$program" ]; then
        # If the folder is 'magnemites' but the executable is named differently, 
        # you can hardcode it here, but usually, they match.
        continue
    fi

    # Clean and recreate program-specific output folder
    rm -rf "$output_dir/$program"
    mkdir -p "$output_dir/$program"

    # 5. Iterate through specific test cases (e.g., easy-1, medium-2)
    for test_case_path in "$program_path"/*; do
        [ -d "$test_case_path" ] || continue
        test_name=$(basename "$test_case_path")

        input_file="$test_case_path/input.txt"
        expected_output_file="$test_case_path/output.txt"
        
        # Define where student results go
        mkdir -p "$output_dir/$program/$test_name"
        student_output="$output_dir/$program/$test_name/output.txt"
        student_diff="$output_dir/$program/$test_name/output.diff"

        # 6. Run the student program with a 3s timeout
        # Using "./$program" ensures it executes the local compiled file
        "./$program" "$input_file" "$student_output" > /dev/null 2>&1        
        exit_code=$?

        # 7. Check Exit Codes
        if [ $exit_code -eq 124 ]; then
            echo "$program $test_name: TIMEOUT"
            continue
        elif [ $exit_code -eq 139 ]; then
            echo "$program $test_name: SEGMENTATION FAULT"
            continue
        elif [ $exit_code -ne 0 ]; then
            echo "$program $test_name: ERROR (exit code $exit_code)"
            continue
        fi

        # 8. Compare results using diff
        if [ -f "$expected_output_file" ]; then
            diff -b "$expected_output_file" "$student_output" > "$student_diff"
            if [ $? -ne 0 ]; then
                echo "$program $test_name: INCORRECT OUTPUT"
            else
                echo "$program $test_name: CORRECT OUTPUT"
            fi
        else
            echo "$program $test_name: MISSING EXPECTED OUTPUT FILE"
        fi
    done
done