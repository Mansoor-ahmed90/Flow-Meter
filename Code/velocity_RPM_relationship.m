% METRIC STANDARD TABLE FOR " AA CURRENT METER "
%       VELOCITY METER PER SECOND
%       Equation : v=(2.2048R + 0.0178)x0.3048
%               Here :   R = revolutions per second

A = zeros(1,31);
P = zeros(1,31);
for R=10:5:60


for T = 40:70 
   A(1,(T-39)) = R/T;
   P(1,(T-39)) = ((2.2048*A(1,(T-39)) + 0.0178)*0.3048);
end
plot(P,A);
hold;

xlabel('Velocity (meter per second)');
ylabel('Revolution Per Second');
title(' Velocity, Revolution Per Second Relationship');
%axis([0 1 0 1])
clear tr yr cn f 


end