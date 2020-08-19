LXRT_LIBLAGS = $(shell /usr/realtime/bin/rtai-config --lxrt-ldflags)
LXRT_CFLAGS = $(shell /usr/realtime/bin/rtai-config --lxrt-cflags)
CC=g++
CFLAGS=-c -Wall
EXTRA_CFLAGS += -I/usr/realtime/include -D__IN_RTAI__

all: microrobot_pc_app

microrobot_pc_app: microrobot_pc_app.o load_b_lut.cpp load_b_lut.h actuation_matrix_calc.cpp actuation_matrix_calc.h matrix.cpp matrix.h data_form_change.cpp data_form_change.h udp_func.cpp udp_func.h gen_BF_ref.cpp gen_BF_ref.h user_input_thread.cpp user_input_thread.h variables.cpp variables.h
	$(CC) microrobot_pc_app.o load_b_lut.cpp actuation_matrix_calc.cpp matrix.cpp data_form_change.cpp udp_func.cpp gen_BF_ref.cpp user_input_thread.cpp variables.cpp $(LXRT_LIBLAGS) -o microrobot_pc_app

microrobot_pc_app.o: microrobot_pc_app.cpp rt_setting.h
	$(CC) $(CFLAGS) $(LXRT_CFLAGS) $(LXRT_LIBLAGS) microrobot_pc_app.cpp

clean:
	rm *.o
