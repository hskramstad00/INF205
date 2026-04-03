import os
import pandas as pd
import matplotlib.pyplot as plt

BENCH_DIR = "benchmark"

scc_file = os.path.join(BENCH_DIR, "scc_results.csv")
scc = pd.read_csv(scc_file)

scc_avg = scc.groupby(["n", "representation"], as_index=False)["time_ms"].mean()

plt.figure(figsize=(8, 5))
for rep in scc_avg["representation"].unique():
    subset = scc_avg[scc_avg["representation"] == rep].sort_values("n")
    plt.plot(
        subset["n"].to_numpy(),
        subset["time_ms"].to_numpy(),
        marker="o",
        label=rep
    )

plt.xlabel("Number of nodes (n)")
plt.ylabel("Average runtime (ms)")
plt.title("SCC runtime scaling")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig(os.path.join(BENCH_DIR, "scc_plot.png"))
plt.close()

diamond_file = os.path.join(BENCH_DIR, "diamond_results.csv")
diamond = pd.read_csv(diamond_file)

diamond_avg = diamond.groupby(
    ["scenario", "n", "representation"], as_index=False
)["time_ms"].mean()

for scenario in diamond_avg["scenario"].unique():
    plt.figure(figsize=(8, 5))
    scenario_data = diamond_avg[diamond_avg["scenario"] == scenario]

    for rep in scenario_data["representation"].unique():
        subset = scenario_data[scenario_data["representation"] == rep].sort_values("n")
        plt.plot(
            subset["n"].to_numpy(),
            subset["time_ms"].to_numpy(),
            marker="o",
            label=rep
        )

    plt.xlabel("Number of nodes (n)")
    plt.ylabel("Average runtime (ms)")
    plt.title(f"Diamond runtime scaling ({scenario})")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(BENCH_DIR, f"diamond_{scenario}.png"))
    plt.close()

print("Plots saved in benchmark/")