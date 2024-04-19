OBJS = ehdecay.o haber.o feynhiggs.o hsqsq.o susylha.o hgaga.o dmb.o elw.o hgg.o

#FFLAGS = -fno-emulate-complex -fno-automatic -ffixed-line-length-none -ffast-math -march=pentiumpro -malign-double -Wall -fno-silent

FFLAGS =

FC=gfortran

.f.o:
	$(FC) -c $(FFLAGS) $*.f

ehdecay: $(OBJS)
	$(FC) $(FFLAGS) $(OBJS) -o run

clean:
	rm -f $(OBJS)
