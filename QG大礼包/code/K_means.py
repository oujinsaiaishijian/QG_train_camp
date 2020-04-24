from numpy import *


class KMeansCluster:

    def __init__(self, n_clusters=3, max_iter=300):

        self.centroids = None
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.clusterAssment = None
        self.labels = None
        self.sse = None

    # creating the center of cluster
    def _randCent(self, X, k):
        n = X.shape[1]
        centroids = empty((k, n))
        for j in range(n):
            minJ = min(X[:, j])
            rangeJ = float(max(X[:, j]) - minJ)
            centroids[:, j] = (minJ + rangeJ * random.rand(k, 1)).flatten()
        return centroids

    def fit(self, X):
        # 类型检查
        if not isinstance(X, ndarray):
            try:
                X = asarray(X)
            except:
                raise TypeError("numpy.ndarray required for X")
        # m代表样本数量
        m = X.shape[0]
        # m*2的矩阵，第一列存储样本点所属的族的索引值，第二列存储该点与所属族的质心的距离
        self.clusterAssment = empty((m, 2))

        self.centroids = self._randCent(X, self.n_clusters)

        # 最多运行max_iter次，多次随机化，可能使得聚类性能提高
        for _ in range(self.max_iter):
            clusterChanged = False
            # 将每个样本点分配到离它最近的质心所属的族
            for i in range(m):
                minDist = inf
                minIndex = -1
                for j in range(self.n_clusters):
                    distJI = self._distEclud(self.centroids[j, :], X[i, :])
                    if distJI < minDist:
                        minDist = distJI
                        minIndex = j
                if self.clusterAssment[i, 0] != minIndex:
                    clusterChanged = True
                    self.clusterAssment[i, :] = minIndex, minDist ** 2
            # # 若所有样本点所属的族都不改变,则已收敛，结束迭代，就是跳出最大的for循环
            if not clusterChanged:
                break
            # 如果没有能跳出来，那就更新质心，即将每个族中的点的均值作为质心
            for i in range(self.n_clusters):
                # 取出属于第i个族的所有点
                ptsInClust = X[nonzero(self.clusterAssment[:, 0] == i)[0]]
                self.centroids[i, :] = mean(ptsInClust, axis=0)
        self.labels = self.clusterAssment[:, 0]
        self.sse = sum(self.clusterAssment[:, 1])

        return self

    def _distEclud(self, vecA, vecB):
        return sqrt(sum((vecA - vecB) ** 2))

    def __repr__(self):
        return "KMeansCluster()"
