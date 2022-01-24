unsigned power(unsigned x, unsigned y){
  if(y == 0){
    return 1;
  }
  return power(x,y-1) * x;
}
