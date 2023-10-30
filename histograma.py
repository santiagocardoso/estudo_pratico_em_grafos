import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('histograma.csv')

num_clusters = df['Cluster']
quantidade_componentes = df['Componentes']

plt.bar(range(1, len(num_clusters) + 1), quantidade_componentes)

plt.xlabel('Clusters')
plt.ylabel('Quantidade de Componentes')

plt.xticks(range(1, len(num_clusters) + 1), num_clusters)

plt.show()
