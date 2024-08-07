#!/bin/bash

# Configuration
LAB_NO=2       # Change this to the appropriate lab number
TIME_LIMIT="3"  # Set this to the time limit for each test case execution in seconds, or leave empty for no limit

# Directories
PROGRAMS_DIR="Programs"                    # Directory containing student program directories
TESTCASES_DIR="testcases"                  # Directory containing input test cases
EXPECTED_OUTPUTS_DIR="expected_outputs"    # Directory containing expected output for test cases
ACTUAL_OUTPUTS_DIR="actual_outputs"        # Directory to store actual outputs generated by student programs
RESULTS_DIR="results"                      # Directory to store grading results

# Create necessary directories
mkdir -p $RESULTS_DIR
mkdir -p $ACTUAL_OUTPUTS_DIR

# Clean up previous results
rm -rf $ACTUAL_OUTPUTS_DIR/*
rm -rf $RESULTS_DIR/*

# Determine the number of questions based on the number of directories in testcases
NUM_Qs=$(ls -d $TESTCASES_DIR/Q* | wc -l)

# Iterate over each student directory in the Programs directory
for student_dir in $PROGRAMS_DIR/*; do
    if [[ -d $student_dir ]]; then
        # Extract the student's roll number from the directory name
        dir_name=$(basename $student_dir)
        rollno=$(echo $dir_name | cut -d'_' -f1)  # Split using '_' and get the first part

        echo "Grading $rollno..."

        # Iterate over each question for the lab
        for q_no in $(seq 1 $NUM_Qs); do
            question_results="$RESULTS_DIR/Q$q_no"
            mkdir -p $question_results

            # Log file for this student's question
            student_log="$question_results/$rollno.txt"
            echo "Evaluating Q$q_no for $rollno" > $student_log

            # Compile the student's code
            cpp_file="$student_dir/${rollno}_LAB${LAB_NO}_Q${q_no}.cpp"
            if [[ -f $cpp_file ]]; then
                g++ $cpp_file -o $student_dir/a.out 2>> $student_log
                if [[ $? -ne 0 ]]; then
                    echo "Compilation failed for $cpp_file" >> $student_log
                    continue
                fi
            else
                echo "File $cpp_file not found." >> $student_log
                continue
            fi

            # Iterate over each test case
            total_score=0
            num_tests=0
            for test_input in $TESTCASES_DIR/Q$q_no/*.in; do
                test_name=$(basename $test_input .in)
                test_output="$ACTUAL_OUTPUTS_DIR/$rollno/Q$q_no/${test_name}.out"
                expected_output="$EXPECTED_OUTPUTS_DIR/Q$q_no/${test_name}.out"
                mkdir -p "$(dirname $test_output)"

                # Run the student's program, using a timeout if specified
                if [[ -n $TIME_LIMIT ]]; then
                    timeout $TIME_LIMIT $student_dir/a.out < $test_input > $test_output
                    if [[ $? -eq 124 ]]; then
                        echo "Test $test_name: Time limit exceeded" >> $student_log
                        continue
                    fi
                else
                    $student_dir/a.out < $test_input > $test_output
                fi

                # Compare the actual output with the expected output
                if diff -q -b -B $test_output $expected_output > /dev/null; then
                    echo "Test $test_name: PASS" >> $student_log
                    ((total_score++))
                else
                    echo "Test $test_name: FAIL" >> $student_log
                fi

                ((num_tests++))
            done

            # Log total score for this question
            echo "Total Score for Q$q_no: $total_score/$num_tests" >> $student_log
            echo "$rollno,$total_score" >> "$question_results/total.csv"
            
            # Remove the compiled executable
            rm -f $student_dir/a.out
        done
    fi
done

echo "Grading completed."
