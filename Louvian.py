import matplotlib.pyplot as plt
import networkx as nx
import pandas as pd
from community import community_louvain
import matplotlib.cm as cm
import math
import seaborn as sns
import numpy as np
from matplotlib import rcParams

def read_graph(s):
    with open(s, 'r') as file:
        lines = file.readlines()
        t = 0
        for line in lines:
            k = line.split(' ')
            if t == 0:
                n = int(k[0])
                for i in range(n):
                    G.add_node(i)
                m = int(k[1])
                t = 1
            else:
                G.add_edge(int(k[0]), int(k[1]))


def get_subgraph(id, g, community):  # get the subgraph in graph g with the id
    g_ = nx.Graph()
    for i in range(g.number_of_nodes()):
        if community[i] == id:
            g_.add_node(i)
    for j in g.edges:
        u, v = j
        if community[u] == id and community[v] == id:
            g_.add_edge(u, v)
    return g_

G = nx.Graph()
# read_graph('Facebook4039.txt')
read_graph('generated.txt')
# x = np.linspace(1, 100, 100)
# y = np.power(0.95, x)
# y[y < 0.2] = 0.2
# plt.plot(y, c='red')
# y = 6 * 0.95 / (x + 5)
# y[y < 0.2] = 0.2
# plt.plot(y, c='blue')
# plt.show()

# print('average clustering', nx.average_clustering(G))
# cc = nx.connected_components(G)
# for g in cc:
#     g = G.subgraph(g)
#     print('diameter', nx.diameter(g))
# cc = nx.connected_components(G)
# for g in cc:
#     g = G.subgraph(g)
#     print('average shortest path length', nx.average_shortest_path_length(g))

# print('louvaining......')
# # use resolution to control the size of each community
# partition = community_louvain.best_partition(G, resolution=0.1, random_state=1)
# print(max(partition.values()) + 1)
size = []
diameter = []
bridge = []
cluster = []
k = 0
# for i in range(max(partition.values()) + 1):
#     g = get_subgraph(i, G, partition)
#     for sub_g in nx.connected_components(g):
#         sub_g = g.subgraph(sub_g)
#         k = k + 1
#         if sub_g.number_of_nodes() < 3:
#             continue
#         size.append(math.log10(sub_g.number_of_nodes()))
#         diameter.append(nx.diameter(sub_g) / (math.log10(sub_g.number_of_nodes()) + 1))
#         bridge.append(len(list(nx.bridges(sub_g))) / (sub_g.number_of_edges() + 1))
#         cluster.append(nx.average_clustering(sub_g))
# print('community =', k)
with open('community.txt', 'r') as file:
    communities = file.readlines()
    for line in communities:
        c = line.split(' ')
        g = nx.Graph()
        for node in c:
            g.add_node(int(node))
        g = G.subgraph(g)
        cc = nx.connected_components(g)
        for sub_g in cc:
            sub_g = g.subgraph(sub_g)
            if sub_g.number_of_nodes() == 1:
                continue
            # print(sub_g)
            size.append(math.log10(sub_g.number_of_nodes()))
            diameter.append(nx.diameter(sub_g) / (math.log10(sub_g.number_of_nodes()) + 1))
            bridge.append(len(list(nx.bridges(sub_g))) / (sub_g.number_of_edges()))
            cluster.append(nx.average_clustering(sub_g))


plt.figure(figsize=(15, 10))
rcParams.update({'font.size': 20})
plt.suptitle('Distance Hop Generator (n=5000, real/expected edge=7963/9296, f=11/(x+10)*0.95)')
bin_number = 50

plt.subplot(2, 2, 1)
# weights = np.ones_like(size) / len(size)
# plt.hist(size, weights=weights, bins=bin_number)
sns.histplot(size, stat='probability', bins=bin_number)
plt.yscale('log')
plt.xlim(-0.1, 4.1)
plt.ylim(0.0008, 2)
# plt.hist(size, bins=20)
plt.title('log10(Size)')

plt.subplot(2, 2, 2)
# weights = np.ones_like(diameter) / len(diameter)
# plt.hist(diameter, weights=weights, bins=bin_number)
sns.histplot(diameter, stat='probability', bins=bin_number)
plt.yscale('log')
plt.xlim(-0.1, 10.1)
plt.ylim(0.0008, 2)
plt.title('Diameter')

plt.subplot(2, 2, 3)
# weights = np.ones_like(bridge) / len(bridge)
# plt.hist(bridge, weights=weights, bins=bin_number)
sns.histplot(bridge, stat='probability', bins=bin_number)
plt.yscale('log')
plt.xlim(-0.1, 1.1)
plt.ylim(0.0008, 2)
plt.title('Bridges')

plt.subplot(2, 2, 4)
# weights = np.ones_like(cluster) / len(cluster)
# plt.hist(cluster, weights=weights, bins=bin_number)
sns.histplot(cluster, stat='probability', bins=bin_number)
plt.yscale('log')
plt.xlim(-0.1, 1.1)
plt.ylim(0.0008, 2)
plt.title('Clustering Coefficient')

plt.show()

# 格式整理
# df_com = pd.DataFrame({'Group_id':com.values(),
#                        'object_id':com.keys()}
#                     )
# df_com.groupby('Group_id').count().sort_values(by='object_id', ascending=False)
# numOfCommunity = max(df_com['Group_id']) + 1
# print(numOfCommunity)
