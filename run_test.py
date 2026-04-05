import os

# --- CONFIG ---
EXEC = "./build/sorting_algorithms"
RES = "res.csv"
ITERS = 50

# --- DICTS FLAG ---
# Algorithms
algos = {"Bucket": 4, "Quick": 5, "Shell": 6}

# Data structures
structs = {"Array": 0, "SList": 1, "DList": 2}

# Non-linear structures
structs_omega = {"Stack": 4, "BST": 5}

# Distributions
dists = {"Random": 0, "Ascending": 1, "Descending": 2, "HalfSorted": 3}

# Data types
types = {"Int": 0, "Float": 1, "Unsigned": 5, "String": 4}

# --- SIZE PARAMETERS ---
sizes_A = [10000, 25000, 50000, 100000]
mid_size = 25000

def run_cmd(alg, struct, typ, dist, data_size, pivot_val=-1, shell_val=-1):
    cmd = f"{EXEC} --benchmark -a {alg} -s {struct} -t {typ} -d {dist} -l {data_size} -n {ITERS} -r {RES} -p {pivot_val} -e {shell_val}"
    print(f" Running: {cmd}")
    os.system(cmd)

def write_divider(text):
    with open(RES, "a") as f:
        f.write(f"--- {text} ---;;;;;;;\n")

print("BEGINNING TESTS...\n")

with open(RES, "w") as f:
    f.write("Algorithm;Structure;DataType;Distribution;Pivot(Quick);Size;Iterations;AverageTime_ms\n")

# ==========================================
# TEST ALFA: Influence of program parameters
# ==========================================
print("\n--- TEST ALFA ---")
write_divider("TEST ALFA: Parameters influence")
# Shella: 0 = Original, 1 = Knuth
for shell_gap in [0, 1]:
    run_cmd(algos["Shell"], structs["Array"], types["Int"], dists["Random"], mid_size, shell_val=shell_gap)

# Quick: three pivots (0 = Random, 1 = Left, 3 = Middle)
for pivot in [0, 1, 3]:
    run_cmd(algos["Quick"], structs["Array"], types["Int"], dists["Random"], mid_size, pivot_val=pivot)

# Best parameters
OPT_PIVOT = 3  # Middle
OPT_SHELL = 1  # Knuth

# ==========================================
# TEST A: Size influence
# ==========================================
print("\n--- TEST A ---")
write_divider("TEST A: Size influence")
for size in sizes_A:
    for alg_name, alg_val in algos.items():
        for struct_name, struct_val in structs.items():
            run_cmd(alg_val, struct_val, types["Int"], dists["Random"], size, pivot_val=OPT_PIVOT, shell_val=OPT_SHELL)

CHOSEN_SIZE = 50000
CHOSEN_ALG = algos["Quick"]

# ==========================================
# TEST B: Distribution influence
# ==========================================
print("\n--- TEST B ---")
write_divider("TEST B: Distribution influence")
for struct_name, struct_val in structs.items():
    for dist_name, dist_val in dists.items():
        run_cmd(CHOSEN_ALG, struct_val, types["Int"], dist_val, CHOSEN_SIZE, pivot_val=OPT_PIVOT)

# ==========================================
# TEST C: Data type influence
# ==========================================
print("\n--- TEST C ---")
write_divider("TEST C: Data type influence")
for type_name, type_val in types.items():
    run_cmd(CHOSEN_ALG, structs["Array"], type_val, dists["Random"], CHOSEN_SIZE, pivot_val=OPT_PIVOT)

# ==========================================
# TEST OMEGA: Non-linear data structures
# ==========================================
print("\n--- TEST OMEGA ---")
write_divider("TEST OMEGA: Non-linear structures")
all_structs_omega = {**structs, **structs_omega}
for struct_name, struct_val in all_structs_omega.items():
    run_cmd(CHOSEN_ALG, struct_val, types["Int"], dists["Random"], CHOSEN_SIZE, pivot_val=OPT_PIVOT)

print("\nALL TESTS HAVE BEEN FINISHED. RESULTS IN ", RES)