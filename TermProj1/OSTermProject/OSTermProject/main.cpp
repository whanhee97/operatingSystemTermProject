#include<iostream>
#include<Windows.h>
#include"Queue.h"
using namespace std;

void runningState(Queue& jq, Queue& rq, Queue& dq1, Queue& dq2, pcb* cpu);
int main() {
	Queue jobQueue;
	Queue readyQueue;
	Queue keyboardQueue;
	Queue mouseQueue;
	pcb* runningPCB = NULL; // CPU에서 수행중인 프로세스
	pcb* temp;
	

	for (int i = 1; i <= 7; i++) { //잡큐에 프로세스블럭 생성
		pcb* temp = new pcb(i);
		jobQueue.push(*temp);
		runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);
		
	}

	
	cout << endl << "job queue -> ready queue " << endl << endl;
	Sleep(1000);

	for (int i = 1; i <= 4; i++) { //레디큐에 패치
		
		temp = &jobQueue.pop();
		temp->setProcessState("ready");
		readyQueue.push(*temp);
		runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);
	}

	///// 최초 실행 /////////

	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////////////////////////

	for (int i = 0; i < 3; i++) {
		cout << "timer interupt occur!" << endl << endl; // 타이머 인터럽트 발생
		Sleep(1000);

		runningPCB->setProcessState("ready"); // 레디상태로 바꾸고
		readyQueue.push(*runningPCB); // 다시 레디큐에 들어감
		runningPCB = &readyQueue.pop();
		runningPCB->setProcessState("running");
		runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);
	}


	//////키보드 입력발생
	cout << "keyboard input occur! (CPU -> Keyboar Queue)" << endl<< endl; // 키보드 입력 발생
	Sleep(1000);

	runningPCB->setProcessState("waiting"); // waiting 상태로 바꾸고
	keyboardQueue.push(*runningPCB); // 키보드 큐에 들어감
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	// 잡큐에서 하나 가져오기
	temp = &jobQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);


	cout << "keyboard input complete! (Keyboar Queue -> Ready Queue)" << endl << endl; // 키보드 입력 완료
	Sleep(1000);
	temp = &keyboardQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	cout << "Mouse input occur! (CPU -> Mouse Queue)" << endl << endl; // 마우스 입력 발생
	Sleep(1000);
	runningPCB->setProcessState("waiting"); // waiting 상태로 바꾸고 
	mouseQueue.push(*runningPCB);
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	cout << "Mouse input occur! (CPU -> Mouse Queue)" << endl << endl; // 마우스 입력 발생
	Sleep(1000);
	runningPCB->setProcessState("waiting"); // waiting 상태로 바꾸고 
	mouseQueue.push(*runningPCB);
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	cout << "Mouse input complete! (Mouse Queue -> Ready Queue)" << endl << endl; // 마우스 입력 완료
	Sleep(1000);
	temp = &mouseQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);


	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	// 잡큐에서 하나 가져오기
	temp = &jobQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);


	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	// 잡큐에서 하나 가져오기 -> 잡큐에 모든 PCB 레디큐로 가져옴
	temp = &jobQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB); 


	cout << "Mouse input complete! (Mouse Queue -> Ready Queue)" << endl << endl; // 마우스 입력 완료
	Sleep(1000);
	temp = &mouseQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // 런닝상태로 바꾸고 -> 레디큐에 있는 모든 PCB 종료됨
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////프로세스 종료
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB; // 모든 PCB 종료
	runningPCB = NULL;
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	return 0;
}

void runningState(Queue& jq, Queue& rq, Queue& dq1, Queue& dq2, pcb* cpu) {
	if (cpu != NULL) {
		cout << "Running : [PID]" << cpu->getPid() << "("<< cpu->getProcessState() << ")" << endl;
	}
	else {
		cout << "Running : "<< endl;
	}
	cout << "Ready Queue : "; rq.printAll();
	cout << "Keyboard Queue : "; dq1.printAll();
	cout << "Mouse Queue : "; dq2.printAll();
	cout << "Job Queue : "; jq.printAll();
	cout << endl;
	Sleep(1000);
}