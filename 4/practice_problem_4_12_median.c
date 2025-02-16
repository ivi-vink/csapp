word Median3 = [
	(B <= A && A <= C) || (C <= A && A <= B) : A;
	(A <= B && B <= C) || (C <= B && B <= A) : B;
	1 : C;
];

