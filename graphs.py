import pandas as pd
import matplotlib.pyplot as plt
import io

print("Inicjalizacja inteligentnego parsera CSV...")

csv_lines = []
current_test = 'UNKNOWN'

with open('res.csv', 'r') as f:
    header = f.readline().strip()
    csv_lines.append(header + ";TestName\n")

    for line in f:
        line = line.strip()
        if not line: continue

        if line.startswith('---'):
            if 'TEST ALFA' in line:
                current_test = 'ALFA'
            elif 'TEST A' in line:
                current_test = 'A'
            elif 'TEST B' in line:
                current_test = 'B'
            elif 'TEST C' in line:
                current_test = 'C'
            elif 'TEST OMEGA' in line:
                current_test = 'OMEGA'
            continue

        if line.startswith('Algorithm'):
            continue

        csv_lines.append(line + f";{current_test}\n")

csv_data = ''.join(csv_lines)
df = pd.read_csv(io.StringIO(csv_data), sep=';')

plt.figure(figsize=(10, 6))
test_a = df[df['TestName'] == 'A']

for (alg, struct), group in test_a.groupby(['Algorithm', 'Structure']):
    plt.plot(group['Size'], group['AverageTime_ms'], marker='o', linewidth=2, label=f'{alg} ({struct})')

plt.yscale('log')
plt.xlabel('Rozmiar struktury (N)', fontsize=12)
plt.ylabel('Średni czas [ms] (Skala Logarytmiczna)', fontsize=12)
plt.title('Test A: Wpływ rozmiaru i struktury na wydajność', fontsize=14, fontweight='bold')
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.tight_layout()
plt.savefig('wykres_Test_A.png', dpi=300)
plt.close()
print(" Wygenerowano: wykres_Test_A.png")

plt.figure(figsize=(10, 6))
test_b = df[df['TestName'] == 'B']

pivot_b = test_b.pivot_table(index='Distribution', columns='Structure', values='AverageTime_ms')
pivot_b = pivot_b.reindex(['Ascending', 'Descending', 'HalfSorted', 'Random'])

pivot_b.plot(kind='bar', figsize=(10, 6), edgecolor='black')
plt.yscale('log')
plt.xlabel('Rozkład danych', fontsize=12)
plt.ylabel('Średni czas [ms] (Skala Logarytmiczna)', fontsize=12)
plt.title('Test B: Wpływ rozkładu danych na QuickSort (N=50 000)', fontsize=14, fontweight='bold')
plt.xticks(rotation=0)
plt.legend(title="Struktura")
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('wykres_Test_B.png', dpi=300)
plt.close()
print(" Wygenerowano: wykres_Test_B.png")

plt.figure(figsize=(8, 6))
test_c = df[df['TestName'] == 'C']

bars = plt.bar(test_c['DataType'], test_c['AverageTime_ms'], color=['#4C72B0', '#DD8452', '#55A868', '#C44E52'],
               edgecolor='black')
plt.xlabel('Typ zmiennej', fontsize=12)
plt.ylabel('Średni czas [ms]', fontsize=12)
plt.title('Test C: Narzut czasowy w zależności od typu danych', fontsize=14, fontweight='bold')

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width() / 2, yval + (yval * 0.02), round(yval, 2), ha='center', va='bottom',
             fontweight='bold')

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('wykres_Test_C.png', dpi=300)
plt.close()
print(" Wygenerowano: wykres_Test_C.png")

plt.figure(figsize=(8, 6))
test_omega = df[df['TestName'] == 'OMEGA']
test_omega = test_omega.sort_values('AverageTime_ms')

bars = plt.bar(test_omega['Structure'], test_omega['AverageTime_ms'], color=['#8172B2', '#937860', '#8C8C8C'],
               edgecolor='black')
plt.yscale('log')
plt.xlabel('Struktura Danych', fontsize=12)
plt.ylabel('Średni czas [ms] (Skala Logarytmiczna)', fontsize=12)
plt.title('Test Omega: QuickSort na strukturach nieliniowych (N=50 000)', fontsize=14, fontweight='bold')

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width() / 2, yval * 1.1, round(yval, 2), ha='center', va='bottom', fontweight='bold')

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('wykres_Test_Omega.png', dpi=300)
plt.close()
print(" Wygenerowano: wykres_Test_Omega.png")

plt.figure(figsize=(9, 5))

test_a_zoom = df[(df['TestName'] == 'A') &
                 (df['Structure'] == 'Array') &
                 (df['Algorithm'].isin(['QuickSort', 'ShellSort']))]

kolory_algorytmow = {'QuickSort': '#D62728', 'ShellSort': '#e377c2'}
for alg, group in test_a_zoom.groupby('Algorithm'):
    plt.plot(group['Size'], group['AverageTime_ms'], marker='o', linewidth=2,
             label=f'{alg} (Array)', color=kolory_algorytmow[alg])

plt.xlabel('Rozmiar struktury (N)', fontsize=12)
plt.ylabel('Średni czas [ms]', fontsize=12)
plt.title('Test A (Przybliżenie): Liniowa charakterystyka dla ShellSort i QuickSort', fontsize=14, fontweight='bold')

plt.xlim(10000, 100000)
plt.ylim(0, 30)

plt.legend(loc='upper left')
plt.grid(True, linestyle="--", alpha=0.7)
plt.tight_layout()
plt.savefig('wykres_Test_A_Zoom.png', dpi=300)
plt.close()
print(" Wygenerowano: wykres_Test_A_Zoom.png")

print("\nGotowe. Dane są teraz w 100% odizolowane i bezpieczne.")