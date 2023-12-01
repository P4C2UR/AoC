#!/bin/env -S awk -f

BEGIN {
  FS=""
}

#Dla pierwszej linijki
NR == 1 {
  #NF - liczba znaków
  t=NF
  #Dodajemy liczbe znaków do widocznych drzew
  visible=NF
  #Inicjalizujemy tablice:
  #max - najwy¿sze drzewo w danej kolumnie
  #bottom - lista drzew widzianych od dołu w danej kolumnie
  #b_visible - zsynchronizowana lista z bottom,
  #            oznacza drzewa widziane tylko od dołu
  for(i=0;i<NF-2;i++) {
    max[i]=$(i+2)
    bottom[0, i]=$(i+2)
    b_visible[0, i]=1
    for(j=1;j<10;j++)
      bottom[j, i]=-1
  }
  next
}

{
  #Zerujemy tablice przechowując liczbe stron z których widziane jest drzewo
  for(i=0;i<NF-2;i++)
    sides[i]=0
  #Ustawiamy maksymalne drzewo widziane z prawej i lewej
  left=$1
  right=$NF
  #Dodajemy 2 drzewa widziane za pierwsze i ostatnie w danym wierszu
  visible+=2

  #Dla każdego drzewa znajdującego się w środku
  for(i=0;i<NF-2;i++) {

    #Jeżeli drzewo widziane z danej strony jest wyższe niż dotychczasowy max
    #to dodaj mu stronę z której jest widoczne i zmieź max
    if(max[i]<$(i+2)) {
      max[i]=$(i+2)
      sides[i]++
    }
    if(left<$(i+2)) {
      left=$(i+2)
      sides[i]++
    }
    if(right<$(NF-i-1)) {
      right=$(NF-i-1)
      sides[NF-i-3]++
    }

    #Jeżeli drzewo jest niższe niż pierwsze widziane od dołu w danej kolumnie
    #to dodaj je na początek listy przesuwając reszte dalej
    if(bottom[0, i]>$(i+2)) {
      for(j=9;j>0;j--) {
        bottom[j, i] = bottom[j-1, i]
        b_visible[j, i] = b_visible[j-1, i]
      }
      bottom[0, i]=$(i+2)
    }
    #W przeciwnym wypadku zamień pierwsze drzewo na aktualne i
    #usuń wszystkie drzewa mniejsze lub równe mu z listy
    else {
      bottom[0, i]=$(i+2)
      for(j=1;j<10;j++) {
        if(bottom[j, i]==-1) break;
        if(bottom[j, i]<=$(i+2)) {
          for(k=j;k<9;k++) {
            bottom[k, i] = bottom[k+1, i]
            b_visible[k, i] = b_visible[k+1, i]
          }
          bottom[9, i] = -1
          b_visible[9, i] = 0
          j--;
        }
      }
    }
  }
  #Dla każdego drzewa jeżeli nie jest widziane z żadnej strony to
  #zapisz to w tablicy b_visible, w przeciwnym wypadku dodaj je do widzianych
  for(i=0;i<NF-2;i++) {
    if(sides[i]!=0) {
      visible++
      b_visible[0, i]=0
    }
    else
      b_visible[0, i]=1
  }
}

END {
  #Dodaj wszystkie drzewa widziane tylko od dołu do licznika drzew widzianych
  for(i=0;i<t-2;i++) {
    for(j=0;j<10;j++) {
      visible+=b_visible[j, i]
    }
  }
  print visible
}
