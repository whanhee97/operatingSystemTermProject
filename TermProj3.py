# TermProject3 - Banker's Algorithms
# 경희대학교 2016104156 컴퓨터공학과 이환희

################# 프로세스 클래스 정의 ####################
class Process:
    def __init__(self,name): # 프로세스 이름넣고 생성
        self.name = name
        self.Max = [0 for _ in range(4)]
        self.Allocation = [0 for _ in range(4)]
        self.Needs = [0 for _ in range(4)]
        self.isFinish = False


    def setMax(self,A,B,C,D): # 맥스 설정
        self.Max[0] = A
        self.Max[1] = B
        self.Max[2] = C
        self.Max[3] = D
    
    def setAlloc(self,A,B,C,D): # 할당 설정
        self.Allocation[0] = A
        self.Allocation[1] = B
        self.Allocation[2] = C
        self.Allocation[3] = D

    def calNeeds(self): # 니즈 계산
         for i in range(4):
            self.Needs[i] = self.Max[i] - self.Allocation[i]
    
    def p_request(self,A,B,C,D): # 리퀘스트 처리 : 리퀘스트가 들어오면 할당량을 증가하고 니즈를 계산
        self.Allocation[0] += A
        self.Allocation[1] += B
        self.Allocation[2] += C
        self.Allocation[3] += D
        self.calNeeds()

    def canAlloc(self,A,B,C,D): # 할당 가능한지 판단 파라미터는 Available의 자원
        aa = A - self.Needs[0]
        bb = B - self.Needs[1]
        cc = C - self.Needs[2]
        dd = D - self.Needs[3]
        if aa>=0 and bb>=0 and cc>=0 and dd>=0:
            return True
        else:
            return False

    def getNeeds(self):
        return self.Needs

    def alloc_returnMax(self): # 할당을 하고 맥스를 리턴해줌 
        for i in range(4):
            self.Allocation[i] = self.Max[i] # 할당량을 맥스와 같게 만들어준 뒤
        self.calNeeds() # 니즈를 계산하면 니즈는 0000이 됨.
        self.isFinish = True # 끝났다고 체크해주고 
        return self.Max # Available 계산을 위해 맥스 반환.

############ 프로세스 생성 ###############
p0 = Process(0)
p1 = Process(1)
p2 = Process(2)
p3 = Process(3)
p4 = Process(4)


############### 할당해주는 함수 정의 ###############
def alloc(p, available, finish): # 할당할때 수행하는 함수
    needs = p.getNeeds() # 니즈를 받아서
    for i in range(4):
        available[i] -= needs[i] # 빼준뒤
    
    Max = p.alloc_returnMax() # p내부 함수 수행 후 맥스 받아서
    for i in range(4):
        available[i] += Max[i] # 더해줌
    
    finish.append(p) # p는 finish로 들어감

def request(p,A,B,C,D): # 리퀘스트를 받을때 수행하는 함수
    Available[0]-=A
    Available[1]-=B
    Available[2]-=C
    Available[3]-=D
    p.p_request(A,B,C,D)

    

############# 실행 부분 ################

p0.setMax(6,0,1,2)
p0.setAlloc(4,0,0,1)
p0.calNeeds()

p1.setMax(1,7,5,0)
p1.setAlloc(1,1,0,0)
p1.calNeeds()

p2.setMax(2,3,5,6)
p2.setAlloc(1,2,5,4)
p2.calNeeds()

p3.setMax(1,6,5,3)
p3.setAlloc(0,6,3,3)
p3.calNeeds()

p4.setMax(1,6,5,6)
p4.setAlloc(0,2,1,2)
p4.calNeeds()

processes = [p0,p1,p2,p3,p4] 

Available = [3,2,1,1]

finish = [] # 자원 다 반납한 프로세스 리스트

########## P4에 (1,2,0,0)을 할당하고 싶으면 바로 아래의 주석 제거 ####################
#request(processes[4],1,2,0,0)

while 1:
    isSafe = False
    for p in processes: #프로세스 리스트에서 하나씩 검사
        if p.canAlloc(Available[0],Available[1],Available[2],Available[3]) and not p.isFinish: # 할당할수 있고 끝난 프로세스가 아니면
            alloc(p,Available,finish) # 할당해줌
            isSafe = True
            break
    if len(finish) == 5 or not isSafe: # 전부다 끝났거나(Safe상태) isSafe 체크가 안 되어있으면(Unsafe상태) 종료시킴
        break

if len(finish) == 5: # safe인 경우 시퀀스출력 (finish리스트에 들어간 순서)
    print("Safe!!\n")
    print("Safe Sequence : ",end='')
    for i in range(4):
        print("P{0}".format(finish[i].name),end = " -> ")
    print("P{0}".format(finish[-1].name))

else: # Unsafe 경우
    print("Unsafe!!\n")