
int main(){
  long* a;
  long b;
  long c;
  long d;
  long e;
  long f;
  long g;
  long h;  
  a= malloc(52514*8);
  c= 52500;
  b= c;
  d= 0;
  f= 10000;
  h= 0;
  while(b>0){
    d=d%f;
    e=d;
    b=b-1;
    g=b*2;
    while(g>0){
      if(h>0){
	d=d*b+f*a[b];
      }else{
	d=d*b+f*f/5;
      }
      g=g-1;
      a[b]=d%g;
      d=d/g;
      b=b-1;
      g=b*2;
    }
    h=printf("%04d",e+d/f);
    c= c-14;
    b=c;
  }
}
