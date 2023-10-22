import numpy as np


class forward():

    def __init__(self, *arguments, len, obs) -> None:
        self.A = arguments[0]                          # 转移矩阵
        self.B = arguments[1]                          # 概率分布矩阵
        self.pi = arguments[2]                         # 初始状态概率
        self.T = len                                   # 观测状态序列长度
        self.O = obs                                   # 观测状态序列

        self.P = [0 if x == "R" else 1 for x in self.O]
        
    def alpha(self) -> float:

        alpha = np.empty((self.T, len(self.A)), dtype=float)

        for i in range(len(self.A)):  # 前向算法初始化
            alpha[0][i] = self.pi[i] * self.B[i][self.P[0]]

        for j in range(1, self.T):
            for k in range(len(self.A)):

                alpha[j][k] = sum(alpha[j-1] * self.A[:, k]) * self.B[k][self.P[j]]
        
        prob = sum(alpha[-1,:])
        
        return prob
    

class backward(forward):

    def beta(self) -> float:

        beta = np.empty((self.T, len(self.A)), dtype=float)
        for i in range(len(self.A)):  # 反向算法初始化
            beta[self.T-1][i] = 1.    

        for j in range(self.T-2, -1, -1):
            for k in range(len(self.A)):

                beta[j][k] = sum(self.A[k, :] * self.B[:,self.P[j+1]] * beta[j+1, :])
        
        prob = sum(self.pi * beta[0, :] * self.B[:, self.P[0]])

        return prob


class viterbi(forward):

    def gamma(self) -> list:
        
        delta = np.empty((self.T, len(self.A)), dtype=float)
        psi = np.empty((self.T, len(self.A)), dtype=int)

        for i in range(len(self.A)):  # viterbi 算法初始化
            delta[0][i] = self.pi[i] * self.B[i][self.P[0]]
            psi[0][i] = 0

        for j in range(1, self.T):
            for k in range(len(self.A)):
                
                delta[j][k] = max(delta[j-1] * self.A[:, k]) * self.B[k][self.P[j]]
                psi[j][k] = np.argmax(delta[j-1] * self.A[:, k])

        q_T= np.argmax(delta[self.T-1, :])            # 回溯最优路径
        lst = [q_T]
        for l in range(self.T-2, -1, -1):
            lst.append(psi[l+1][lst[-1]])

        return lst[::-1]

if __name__ == '__main__':

    A = np.array([[0.5, 0.2, .3], [0.3, 0.5, 0.2], [0.2, 0.3, 0.5]])

    B = np.array([[0.5, 0.5], [0.4, 0.6], [0.7, 0.3]])

    pi = np.asarray([0.2, 0.4, 0.4])

    T = 3; O = ["R", "W", "R"]

    prob1 = forward(A, B, pi, len=T, obs=O).alpha()
    prob2 = backward(A, B, pi, len=T, obs=O).beta()
    backtrace = viterbi(A, B, pi, len=T, obs=O).gamma() # 索引从 0 开始
    realtrace = backtrace + np.ones_like((1,))          # 索引从 1 开始

    print("forward algorithm result: ", prob1, "\nbackward algorithm result: ", prob2, 
          "\nviterbi algorithm result: ", realtrace)