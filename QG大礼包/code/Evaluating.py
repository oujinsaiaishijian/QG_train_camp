import numpy as np
import matplotlib.pyplot as plt

# 绘制决策边界，黑箱
def plot_decision_boundary(model, axis):
    x0, x1 = np.meshgrid(
        np.linspace(axis[0], axis[1], int((axis[1] - axis[0]) * 100)).reshape(-1, 1),
        np.linspace(axis[2], axis[3], int((axis[3] - axis[2]) * 100)).reshape(-1, 1),
    )

    X_new = np.c_[x0.ravel(), x1.ravel()]
    y_predict = model.predict(X_new)
    zz = y_predict.reshape(x0.shape)
    from matplotlib.colors import ListedColormap
    custom_cmap = ListedColormap(['#EF9A9A', '#FFF59D', '#90CAF9'])
    plt.contourf(x0, x1, zz, linewidth=5, cmap=custom_cmap)

# Classification assessment
def F1_score(y_ture, y_predict):
    precision = precision_score(y_ture, y_predict)
    recall = recall_score(y_ture, y_predict)
    try:
        return 2 * precision * recall / (precision + recall)
    except:
        return 0.0


def accuracy_score(y_ture, y_predict):
    tp = TP(y_ture, y_predict)
    tn = TN(y_ture, y_predict)
    fp = FP(y_ture, y_predict)
    fn = FN(y_ture, y_predict)

    return (tp + tn) / (tp + tn + fp + fn)


def precision_score(y_ture, y_predict):
    tp = TP(y_ture, y_predict)
    fp = FP(y_ture, y_predict)
    try:
        return tp / (tp + fp)
    except:
        return 0.0


def recall_score(y_ture, y_predict):
    tp = TP(y_ture, y_predict)
    fn = FN(y_ture, y_predict)
    try:
        return tp / (tp + fn)
    except:
        return 0.0


def confusion_matrix(y_ture, y_predict):
    return np.array([
        [TN(y_ture, y_predict), FP(y_ture, y_predict)],
        [FN(y_ture, y_predict), TP(y_ture, y_predict)]
    ])


# true positives
def TP(y_ture, y_predict):
    assert len(y_ture) == len(y_predict)
    return np.sum((y_ture == 1) & (y_predict == 1))


# true negatives
def TN(y_ture, y_predict):
    assert len(y_ture) == len(y_predict)
    return np.sum((y_ture == 0) & (y_predict == 0))


# false positives
def FP(y_ture, y_predict):
    assert len(y_ture) == len(y_predict)
    return np.sum((y_ture == 0) & (y_predict == 1))


# false negatives
def FN(y_ture, y_predict):
    assert len(y_ture) == len(y_predict)
    return np.sum((y_ture == 1) & (y_predict == 0))


# Regression assessment

def mse_test(y_ture, y_predict):
    assert y_ture.shape[0] == y_predict.shape[0], "the size of y_ture must be equal to the size of y_predict"
    mse = np.sum((y_ture - y_predict) ** 2) / len(y_ture)
    return mse


def rmse_test(y_ture, y_predict):
    assert y_ture.shape[0] == y_predict.shape[0], "the size of y_ture must be equal to the size of y_predict"
    rmse = np.sqrt(mse_test(y_ture, y_predict))
    return rmse


def mea_test(y_ture, y_predict):
    assert y_ture.shape[0] == y_predict.shape[0], "the size of y_ture must be equal to the size of y_predict"
    mea = np.sum(np.absolute(y_ture - y_predict)) / len(y_ture)
    return mea


def mape_test(y_ture, y_predict):
    assert y_ture.shape[0] == y_predict.shape[0], "the size of y_ture must be equal to the size of y_predict"
    mape = np.sum(np.absolute(y_ture - y_predict) / y_ture) / len(y_ture)
    return mape


def R_square(y_ture, y_predict):
    assert y_ture.shape[0] == y_predict.shape[0], "the size of y_ture must be equal to the size of y_predict"
    r_square = 1 - mse_test(y_ture, y_predict) / np.var(y_ture)
    return r_square
