micro_robot_app

2020년 8월 19일
3월에 새로 만든 시스템 디지스트에 원격으로 작업하던중에

RUN 상황에서 2번 인버터에서 current reference의 high byte와 low byte의 순서가 뒤바뀌어서 통신으로 들어오는 것을 확인했음.
예상되는 원인은, 마루다 프로그램에서 실수 했을 수 있고, 또는 하드웨어 고장?? 일 수도 있을 것 같음

일단 이를 통신보드에서 바꿔서 해결했음