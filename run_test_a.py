import os

# --- CONFIG ---
EXEC = "./build/sorting_algorithms"
RES = "res.csv"
DETAILS = "details.csv"
ITERS = 50

# --- DICTS FLAG ---
algos = {"Bucket": 4, "Quick": 5, "Shell": 6}
structs = {"Array": 0, "SList": 1, "DList": 2}
structs_omega = {"Stack": 4, "BST": 5}
dists = {"Random": 0, "Ascending": 1, "Descending": 2, "HalfSorted": 3}
types = {"Int": 0, "Float": 1, "Unsigned": 5, "String": 4}

# --- SIZE PARAMETERS ---
sizes_A = [10000, 25000, 50000, 100000]
mid_size = 25000

def run_cmd(alg, struct, typ, dist, data_size, pivot_val=0, shell_val=0):
    cmd = f"{EXEC} --benchmark -a {alg} -s {struct} -t {typ} -d {dist} -l {data_size} -n {ITERS} -r {RES} -p {pivot_val} -e {shell_val}"
    print(f" Running: {cmd}")
    os.system(cmd)

def write_divider(text):
    with open(RES, "a") as f:
        f.write(f"--- {text} ---;;;;;;;\n")

print("CLEANING OLD RESULTS...\n")
if os.path.exists(RES):
    os.remove(RES)
if os.path.exists(DETAILS):
    os.remove(DETAILS)

print("BEGINNING TESTS...\n")

with open(RES, "w") as f:
    f.write("Algorithm;Structure;DataType;Distribution;Pivot(Quick);Size;Iterations;AverageTime_ms\n")

OPT_PIVOT = 3  # Middle
OPT_SHELL = 1  # Knuth

# ==========================================
# TEST ALFA:
# ==========================================
# print("\n--- TEST ALFA ---")
# ...

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
# print("\n--- TEST B ---")
# ...

# ==========================================
# TEST C: Data type influence
# ==========================================
print("\n--- TEST C ---")
write_divider("TEST C: Data type influence")
for type_name, type_val in types.items():
    run_cmd(CHOSEN_ALG, structs["Array"], type_val, dists["Random"], CHOSEN_SIZE, pivot_val=OPT_PIVOT, shell_val=OPT_SHELL)

# ==========================================
# TEST OMEGA: Non-linear data structures
# ==========================================
# print("\n--- TEST OMEGA ---")
# ...

print(f"\nALL REQUIRED TESTS HAVE BEEN FINISHED. RESULTS IN {RES} AND {DETAILS}")