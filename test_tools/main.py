import json
import matplotlib.pyplot as plt

def read_json_lines(filename):
    """Reads a file with one JSON object per line."""
    data = []
    with open(filename, 'r') as f:
        for line in f:
            if line.strip():
                data.append(json.loads(line))
    return data

def safe_float(value):
    try:
        return float(value)
    except (ValueError, TypeError):
        return 0.0

def plot_outputs(data, output_name):
    """Plots out1, out2, and out3 as functions of timestamp."""
    timestamps = [entry["timestamp"] for entry in data]
    out1 = [safe_float(entry.get("out1")) for entry in data]
    out2 = [safe_float(entry.get("out2")) for entry in data]
    out3 = [safe_float(entry.get("out3")) for entry in data]

    plt.figure(figsize=(10, 6))
    plt.plot(timestamps, out1, label="out1", linewidth=2)
    plt.plot(timestamps, out2, label="out2", linewidth=2)
    plt.plot(timestamps, out3, label="out3", linewidth=2)

    plt.xlabel("Timestamp")
    plt.ylabel("Output Value")
    plt.title("Outputs over Time")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(output_name, dpi=300)

def main():
    # file containing JSON lines
    filename1 = "data_client1.json"  
    data1 = read_json_lines(filename1)
    plot_outputs(data1, "outputs_plot_client1.jpg")

    # file containing JSON lines
    filename2 = "data_client2.json"  
    data2 = read_json_lines(filename2)
    plot_outputs(data2, "outputs_plot_client2.jpg")

if __name__ == "__main__":
    main()
