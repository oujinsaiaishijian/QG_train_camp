import numpy as np

# 线性核函数
class LinearKernel():
    def __call__(self, x, y):
        return np.dot(x, y.T)


# 多项式核函数
class PolyKernel(object):
    # 初始化方法
    def __init__(self, degree=2):
        self.degree = degree

    def __call__(self, x, y):
        return np.dot(x, y.T) ** self.degree