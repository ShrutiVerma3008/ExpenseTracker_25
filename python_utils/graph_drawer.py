# graph_drawer.py
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import os

GROUP_FOLDER = "../data/groups/"

# Draw the transaction graph from group CSV
def draw_group_graph(group_name):
    filepath = os.path.join(GROUP_FOLDER, f"{group_name}.csv")
    if not os.path.exists(filepath):
        print("❌ Group file not found.")
        return

    df = pd.read_csv(filepath)
    G = nx.DiGraph()

    # Build graph edges with accumulated weights
    for _, row in df.iterrows():
        payer = row["Payer"]
        payee = row["Payee"]
        amount = row["Amount"]

        if G.has_edge(payer, payee):
            G[payer][payee]['weight'] += amount
        else:
            G.add_edge(payer, payee, weight=amount)

    # Draw graph with curved edges for clarity
    pos = nx.spring_layout(G, seed=42)
    edge_labels = nx.get_edge_attributes(G, 'weight')
    formatted_labels = {k: f"Rs {v:.2f}" for k, v in edge_labels.items()}

    edge_colors = ['green' if G[u][v]['weight'] < 400 else 'red' for u, v in G.edges()]

    plt.figure(figsize=(10, 6))
    nx.draw_networkx_nodes(G, pos, node_color='skyblue', node_size=1500)
    nx.draw_networkx_labels(G, pos, font_size=12, font_weight='bold')
    nx.draw_networkx_edges(G, pos, edgelist=G.edges(), arrowstyle='->', arrowsize=20, edge_color=edge_colors, connectionstyle='arc3,rad=0.2')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=formatted_labels, font_color='darkred')

    plt.title(f"💸 Group Expense Graph: {group_name}")
    plt.axis('off')
    plt.tight_layout()
    plt.show()

# Main Execution
if __name__ == "__main__":
    group_name = input("Enter group name (without .csv): ")
    draw_group_graph(group_name)
