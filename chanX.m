function tag_position = chanX( num_of_anchor,anchor_position, R)
K=eye(2,num_of_anchor-1);
Ga=eye(num_of_anchor-1,3);
h=eye(1,num_of_anchor-1);
reout=[0 
       0];
    Q = eye(num_of_anchor-1);
    m = (anchor_position(1, 1))^2+(anchor_position(2, 1))^2;
    for i = 1: num_of_anchor-1
        K(i) = anchor_position(1,i+1)^2 + anchor_position(2,i+1)^2;
    end
    for i = 1: num_of_anchor-1
        Ga(i,1) = -(anchor_position(1, i+1)-anchor_position(1, 1));
        Ga(i,2) = -(anchor_position(2, i+1)-anchor_position(2, 1));
        Ga(i,3) = -R(i);
    end
    for i = 1: num_of_anchor-1
        h(i) = 0.5*(R(i)^2 - K(i) + m);
    end
    Za0 = inv(Ga'*inv(Q)*Ga)*Ga'*inv(Q)*h';%(14b）
    B = eye(num_of_anchor-1);
    for i = 1: num_of_anchor-1
        B(i,i) = sqrt((anchor_position(1,i+1) - Za0(1))^2 + (anchor_position(2,i+1) - Za0(2))^2);
    end
    FI = B*Q*B;
    Za1 = inv(Ga'*inv(FI)*Ga)*Ga'*inv(FI)*h';%（14a）

    if Za1(3) < 0
        Za1(3) = abs(Za1(3));
    end
    CovZa = inv(Ga'*inv(FI)*Ga);
    sB = eye(3);
   % for i = 1: 3
    %    sB(i,i) = Za1(i);
    %end
    sB(1,1) = Za1(1)-anchor_position(1, 1);
    sB(2,2) = Za1(2)-anchor_position(2, 1);
    sB(3,3) = Za1(3);
    sFI = 4*sB*CovZa*sB;
    sGa = [1, 0; 0, 1; 1, 1];
    sh  = [(Za1(1)-anchor_position(1, 1))^2; (Za1(2)-anchor_position(2, 1))^2; Za1(3)^2];%x1,y1,在此处也进行了运算；
    Za2 = inv(sGa'*inv(sFI)*sGa)*sGa'*inv(sFI)*sh;
    Za = sqrt(abs(Za2));
    reout(1)=anchor_position(1, 1);
    reout(2)=anchor_position(2, 1);
    out = abs(Za)+reout;
    
    if nargout == 1
        tag_position = out;
    elseif nargout == 0
        disp(out);
    end
