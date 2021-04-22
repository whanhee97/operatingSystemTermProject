# TermProject4 - Replacement Algorithms(LRU & Optimal)
# 경희대학교 2016104156 컴퓨터공학과 이환희


############################## 함수 구현 ####################################

#프레임내 존재하는지 존재하면 인덱스 반환하고 아니면 -1 반환
def isExist(frames, num):
    for i in range(4):
        if frames[i][0] == num:
            return i
    return -1

# pageFault날때 삽입메소드
def insertNotExist(frames, num):
    #가장 나이 많은 프레임 인덱스를 찾음
    MaxAge = 0
    MaxAgeIndex = 0
    for i in range(3,-1,-1):
        if frames[i][1] >= MaxAge:
            MaxAge = frames[i][1]
            MaxAgeIndex = i

    #모든 프레임의 age를 1 증가
    for j in range(4):
        frames[j][1] += 1
    #젤 나이 많은 인덱스에 값 넣고 age 0으로 초기화
    frames[MaxAgeIndex][0]=num
    frames[MaxAgeIndex][1]=0

# pageFault 안 날때 삽입메소드
def insertExist(frames, num, index):
    #모든 프레임의 age를 1 증가
    for j in range(4):
        frames[j][1] += 1
    #인덱스 해당하는 프레임에 값 넣고 age 0으로 초기화
    frames[index][0] = num
    frames[index][1] = 0


# 가장 멀리있는 프레임의 인덱스를 구함
def mostFar(frames,currentIndex,referenceStr):
    for i in range(4):# 프레임 4개를 검사해서 각각의 거리를 저장
        distance = 1
        check = False
        for j in range(currentIndex+1,len(referenceStr)):
            if(referenceStr[j] == frames[i][0]): #값과 일치하는게 있으면 멈추고 거리 저장
                frames[i][1] = distance 
                check = True
                break
            distance +=1
        if not check:
            frames[i][1] = 100 #없으면 거리를 100으로 저장
    
    maxDistance = 0
    mostFarIndex = 0
    for i in range(3,-1,-1): #마지막 프레임부터 검사해서 가장 거리가 먼 프레임 인덱스 저장
        if frames[i][1] >= maxDistance:
            maxDistance = frames[i][1]
            mostFarIndex = i
    
    return mostFarIndex # 제일 먼 프레임의 인덱스를 반환

def OptimalInsert(frames,num,currentIndex,referenceStr):
    # 가장 멀리있는 프레임의 인덱스를 구함
    MaxIndex = mostFar(frames,currentIndex,referenceStr)
    # 가장 멀리있는 곳에 num을 넣음
    frames[MaxIndex][0] = num



############################## LRU와 Optimal 구현 ####################################

def LRU(referenceStr):
    LRUframes = [[0,0],[0,0],[0,0],[0,0]] #천번째는 값이 들어가고 두번째는 age가 들어감
    pageFault = 0
    
    for r in referenceStr:
        result = isExist(LRUframes,r) # 존재하면 인덱스 반환하고 존재안하면 -1반환
        
        if result == -1: # 존재하지 않으면
            insertNotExist(LRUframes,r)
            pageFault +=1
        else:
            insertExist(LRUframes,r,result)
    return pageFault


def Optimal(referenceStr):
    OptimalFrames = [[0,0],[0,0],[0,0],[0,0]] # 첫번쨰는 값, 두번쨰는 얼마나 멀리있는지
    pageFault = 0
    
    for i in range(len(referenceStr)):
        result = isExist(OptimalFrames,referenceStr[i])
        if result == -1: # 존재하지 않으면
            OptimalInsert(OptimalFrames,referenceStr[i],i,referenceStr)
            pageFault +=1
        
    return pageFault


############################## 실행 ####################################

referenceStr = [1,2,3,2,5,6,3,4,6,3,7,3,1,5,3,6,3,4,2,4,3,4,5,1]

print("LRU Page Faults : {}".format(LRU(referenceStr)))
print("Optimal Page Faults : {}".format(Optimal(referenceStr)))