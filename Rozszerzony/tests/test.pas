program example(input, output);
var x, y: integer;
var g,h:real;
function f(a, b: real; c: integer):real;
var q:integer;
begin
   q:=4;
   f:=a+b*q
end;

begin
read(x,y);
h:=1.5 +2*3.5;
g:=0;
x:=f(h,x,14);
write(g)
end.
