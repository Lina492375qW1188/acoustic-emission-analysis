
  
 [x,sr]= mp3read('170209_003.mp3');


sr;


fidD=fopen('170209_003.txt','w');


num=length(x(:,1));

for i=1:num
    fprintf(fidD,'%f \r\n',x(i,1));
end
fclose(fidD);   

figure(1);
plot(x(:,1));
xlabel('Time');
title('Amplitude');
