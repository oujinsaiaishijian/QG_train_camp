import numpy as np
from math import log


class Decisiontree:
    def __init__(self):
        # 初始化特征标签，分类的时候用
        self.featLabels = []

    '''
    fit()方法的使用输入了数据集和标签变量，景观算法本身并不需要这个标签变量，
    但是为了给出数据的明确含义，也为了统一，仍然将它作为一个输入参数提供
    '''

    def fit(self, dataSet, labels):
        # 取分类标签
        classList = [example[-1] for example in dataSet]

        # 如果类别完全相同则停止继续划分
        if classList.count(classList[0]) == len(classList):
            return classList[0]
        # 遍历完所有特征时返回出现次数最多的类标签
        if len(dataSet[0]) == 1 or len(labels) == 0:
            return self.majorityCnt(classList)

        # 选择最优特征和它的标签
        bestFeat = self.chooseBestFeatureToSplit(dataSet)
        bestFeatLabel = labels[bestFeat]
        self.featLabels.append(bestFeatLabel)

        # 根据最优特征的标签生成树
        mytree = {bestFeatLabel: {}}
        # 删除已经使用特征标签
        del (labels[bestFeat])
        # 得到训练集中所有最优特征的属性值
        featValues = [example[bestFeat] for example in dataSet]
        # 去掉重复的属性值
        uniqueVals = set(featValues)

        # 遍历特征，创建决策树。
        for value in uniqueVals:
            # 这行代码复制了类标签，并将其储存在新列表变量中，不然就是引用了
            subLabels = labels[:]
            #   self.mytree = mytree
            mytree[bestFeatLabel][value] = self.fit(self.splitDataSet(dataSet, bestFeat, value), subLabels)

        return mytree

    '''
    如果数据集已经处理了所有属性，但是类标签仍然不是唯一的，这个时候我们需要决
    定如何定义该叶子节点，这里我们采用多数表决的方式决定
    '''

    def majorityCnt(self, classList):
        classCount = {}

        for vote in classList:  # 统计classList中每个元素出现的次数
            if vote not in classCount.keys():
                classCount[vote] = 0
                classCount[vote] += 1

        sortedClassCount = sorted(classCount.items(), key=np.operator.itemgetter(1), reverse=True)  # 根据字典的值降序排序

        return sortedClassCount[0][0]

    '''
    下面的函数会遴选出最好的特征，但是调用的这些数据是有要求的，列表，列表元素
    有相同长度就不说了，数据最后一列或者说实例的最后哦一个元素应当是当前实例的
    类别标签，这次给的数据集是满足这个要求的
    
    '''

    # 选择最好的特征进行分类
    def chooseBestFeatureToSplit(self, dataSet):
        # 特征数量
        numFeatures = len(dataSet[0]) - 1
        # 计算数据集的香农熵
        baseEntropy = self.calcShannonEnt(dataSet)
        # 初始化信息增益和最优特征的索引值
        bestInfoGain = 0.0
        bestFeature = -1
        # 遍历所有特征
        for i in range(numFeatures):
            # 获取dataSet的第i个所有特征
            featList = [example[i] for example in dataSet]
            # 创建set集合{},set() 函数创建一个无序不重复元素集
            uniqueVals = set(featList)
            # 初始化经验条件熵
            newEntropy = 0.0

            # 计算信息增益infoGain
            for value in uniqueVals:
                # subDataSet划分后的子集
                subDataSet = self.splitDataSet(dataSet, i, value)
                # 计算子集的概率
                prob = len(subDataSet) / float(len(dataSet))
                # 根据公式计算经验条件熵
                newEntropy += prob * self.calcShannonEnt(subDataSet)
            infoGain = baseEntropy - newEntropy

            # 计算信息增益
            if (infoGain > bestInfoGain):
                # 更新信息增益，找到最大的信息增益
                bestInfoGain = infoGain
                # 记录信息增益最大的特征的索引值
                bestFeature = i

        return bestFeature

    # 计算经验熵
    def calcShannonEnt(self, dataSet):
        # 返回数据集的行数
        numEntires = len(dataSet)
        # 保存每个标签(Label)出现次数的字典
        labelCounts = {}
        # 对每组特征向量进行统计
        for featVec in dataSet:
            # 提取标签(Label)信息，如上面所说，标签在最后一列
            currentLabel = featVec[-1]
            # 如果标签(Label)没有放入统计次数的字典,添加进去
            if currentLabel not in labelCounts.keys():
                labelCounts[currentLabel] = 0
            labelCounts[currentLabel] += 1

        shannonEnt = 0.0
        for key in labelCounts:
            prob = float(labelCounts[key]) / numEntires
            shannonEnt -= prob * log(prob, 2)

        return shannonEnt

    # axis-划分数据集的特征，value-需要返回的特征的值
    def splitDataSet(self, dataSet, axis, value):
        # 创建返回的数据集列表
        retDataSet = []

        for featVec in dataSet:
            if featVec[axis] == value:
                # 去掉axis特征,前取后不取
                reducedFeatVec = featVec[:axis]
                # 将符合条件的添加到返回的数据集
                reducedFeatVec.extend(featVec[axis + 1:])
                retDataSet.append(reducedFeatVec)

        return retDataSet

    '''
    def classify(self, testVec):
        # 获取决策树结点
        firstStr = next(iter(self.mytree))
        # 下一个字典
        secondDict = self.mytree[firstStr]
        featIndex = self.featLabels.index(firstStr)
        for key in secondDict.keys():
            if testVec[featIndex] == key:
                if type(secondDict[key]).__name__ == 'dict':
                    classLabel = self.classify(testVec)
                else:
                    classLabel = secondDict[key]

        return classLabel
    '''



def classify(inputTree, featLabels, testVec):
    firstStr = next(iter(inputTree))  # 获取决策树结点
    secondDict = inputTree[firstStr]  # 下一个字典
    featIndex = featLabels.index(firstStr)
    for key in secondDict.keys():
        if testVec[featIndex] == key:
            if type(secondDict[key]).__name__ == 'dict':
                classLabel = classify(secondDict[key], featLabels, testVec)
            else:
                classLabel = secondDict[key]
    return classLabel

