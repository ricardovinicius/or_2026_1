import random
import argparse
import sys

def generate_bpp_instance(filename, num_items):
    # Calculate a theoretical lower bound to give a benchmark
    total_weight = 0.0
    
    try:
        with open(filename, 'w') as f:
            f.write(f"{num_items}\n")
            for _ in range(num_items):
                # Generate weights between 0.1 and 0.9 (rounded to 2 decimals)
                weight = round(random.uniform(0.1, 0.9), 2)
                total_weight += weight
                f.write(f"{weight}\n")
                
        print(f"Success! Generated '{filename}' with {num_items} items.")
        print(f"Total Weight: {total_weight:.2f}")
        print(f"Absolute Minimum Possible Bins (Lower Bound): {int(total_weight + 0.999)}") # Ceiling
        
    except IOError as e:
        print(f"Error: Could not write to file '{filename}'. Make sure the directory exists.")
        print(e)
        sys.exit(1)

if __name__ == "__main__":
    # Set up the argument parser
    parser = argparse.ArgumentParser(description="Generate Bin Packing Problem (BPP) instances.")
    
    # Define the two required arguments
    parser.add_argument("filename", type=str, help="The path and name of the output file (e.g., instances/test_100.txt)")
    parser.add_argument("num_items", type=int, help="The number of items to generate")
    
    # Parse the arguments from the command line
    args = parser.parse_args()
    
    # Run the generator with the provided arguments
    generate_bpp_instance(args.filename, args.num_items)