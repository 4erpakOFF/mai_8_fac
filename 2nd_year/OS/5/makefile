all: main_st.o libvector.so
	gcc main_st.o -L. -lvector -Wl,-rpath,. -o static.out
	gcc main_d.o -ldl -o dynamic.out


main_static.o: main_st.c
	gcc -c main_st.c

main_dynamic.o: main_d.c
	gcc -c main_d.c


libvector.so: vector.o
	gcc -shared vector.o -o libvector.so

vector.o: vector.c
	gcc -c -fPIC vector.c

clean:
	rm -rf *.o *.so a.out
