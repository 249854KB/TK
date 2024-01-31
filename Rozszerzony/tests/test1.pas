program example(input, output);
var x, y: integer;
var g,h:real;
function f(a, b: real; c: integer):real;
var q:integer;
begin
   q:=4;
   f:=a+b*q
end;
procedure p(a:real; b, c: integer);
begin
if b < c then
    c:=a
  else
    a:= b
end;

begin
read(x,y);
h:=g +h*x;
p(12.0,x,y);
x:=f(h,x,14);
write(g)
end.
