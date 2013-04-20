# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: test_mpu

HDRS = I2Cdev.h MPU6050.h
OBJS = I2Cdev.o MPU6050.o MPU.o test_mpu.o

# Set DMP FIFO rate to 20Hz to avoid overflows on 3d demo.  See comments in
# MPU6050_6Axis_MotionApps20.h for details.

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -g -O2 #`pkg-config gtkmm-3.0 --cflags --libs`

$(OBJS) : $(HDRS)

test_mpu: $(OBJS)
	$(CXX) -o $@ $^  -lm

clean:
	rm -f $(OBJS) test_mpu

