import numpy as np
from kernel import LinearKernel


class SVM():

    def __init__(self, trainX, trainY, C=1, kernel=None, difference=1e-3, max_iter=100):
        # 正则化的参数
        self.C = C
        # 用来判断是否收敛的阈值
        self.difference = difference
        # 迭代次数的最大值
        self.max_iter = max_iter
        # 无核默认是线性的核
        if kernel is None:
            self.kernel = LinearKernel()
        else:
            self.kernel = kernel.kernel
        # 偏置值
        self.b = 0
        # 拉格朗日乘子
        self.alpha = None
        # 特征经过核函数转化的值
        self.K = None
        self.X = trainX
        self.Y = trainY

        self.m = trainX.shape[0]

        self.n = trainX.shape[1]
        # 核的新特征数组初始化
        self.K = np.zeros((self.m, self.m))
        for i in range(self.m):
            # 每一行数据的特征通过核函数转化 n->m
            self.K[:, i] = self.kernel(self.X, self.X[i, :])
        # 拉格朗日乘子初始化
        self.alpha = np.zeros(self.m)

    # SMO算法，对照笔记
    def train(self):
        for now_iter in range(self.max_iter):
            # 深拷贝一下
            alpha_prev = np.copy(self.alpha)
            for j in range(self.m):
                # 选择第二个优化的拉格朗日乘子,在SVM中，SMO要选择一对乘子
                i = self.random_index(j)
                # 计算误差
                error_i = self.error_row(i)
                error_j = self.error_row(j)

                # 检验他们是否满足KKT条件，然后选择违反KKT条件最严重的self.alpha[j]，这样的迭代速度会更快
                if (self.Y[j] * error_j < -0.001 and self.alpha[j] < self.C) or (
                        self.Y[j] * error_j > 0.001 and self.alpha[j] > 0):

                    # 计算eta
                    eta = self.K[i, i] - self.K[j, j] - 2.0 * self.K[i, j]

                    # 要是eta作妖的话那这个迭代岂不是就开始反向作妖了.
                    if eta >= 0:
                        continue

                    # 计算边界值
                    L, H = self.getBounds(i, j)

                    # 旧的拉格朗日乘子的值
                    old_alpha_j, old_alpha_i = self.alpha[j], self.alpha[i]

                    # self.alpha[j]的迭代
                    self.alpha[j] -= (self.Y[j] * (error_i - error_j)) / eta

                    # 根据约束最后更新拉格朗日乘子self.alpha[j]，并且更新self.alpha[j]
                    self.alpha[j] = self.finalValue(self.alpha[j], H, L)
                    self.alpha[i] = self.alpha[i] + self.Y[i] * self.Y[j] * (old_alpha_j - self.alpha[j])

                    # 更新偏置值b
                    b1 = self.b - error_i - self.Y[i] * (self.alpha[i] - old_alpha_j) * self.K[i, i] - \
                         self.Y[j] * (self.alpha[j] - old_alpha_j) * self.K[i, j]
                    b2 = self.b - error_j - self.Y[j] * (self.alpha[j] - old_alpha_j) * self.K[j, j] - \
                         self.Y[i] * (self.alpha[i] - old_alpha_i) * self.K[i, j]
                    if 0 < self.alpha[i] < self.C:
                        self.b = b1
                    elif 0 < self.alpha[j] < self.C:
                        self.b = b2
                    else:
                        self.b = 0.5 * (b1 + b2)

            # 判断是否收敛
            diff = np.linalg.norm(self.alpha - alpha_prev)
            if diff < self.difference:
                break

    # 随机一个要优化的拉格朗日乘子，该乘子必须和循环里面选择的乘子不同
    def random_index(self, first_alpha):
        i = first_alpha
        while i == first_alpha:
            i = np.random.randint(0, self.m - 1)
        return i

    # 用带拉格朗日乘子表示的w代入wx+b
    def predict_row(self, X):
        k_v = self.kernel(self.X, X)
        return np.dot((self.alpha * self.Y).T, k_v.T) + self.b

    # 预测，返回一个判断正确的index的矩阵
    def predict(self, X):
        n = X.shape[0]
        result = np.zeros(n)
        for i in range(n):
            result[i] = np.sign(self.predict_row(X[i, :]))  # 正的返回1，负的返回-1
        return result

    # 预测的值减真实的Y
    def error_row(self, i):
        return self.predict_row(self.X[i]) - self.Y[i]

    # 得到self.alpha[j]的范围约束
    def getBounds(self, i, j):
        if self.Y[i] != self.Y[j]:
            L = max(0, self.alpha[j] - self.alpha[i])
            H = min(self.C, self.C - self.alpha[i] + self.alpha[j])
        else:
            L = max(0, self.alpha[i] + self.alpha[j] - self.C)
            H = min(self.C, self.alpha[i] + self.alpha[j])
        return L, H

    # 根据self.alpha[i]的范围约束获得最终的值
    def finalValue(self, alpha, H, L):
        if alpha > H:
            alpha = H
        elif alpha < L:
            alpha = L
        return alpha
