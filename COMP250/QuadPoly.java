public class QuadPoly extends Poly {
   
    public QuadPoly() {
        super();
    }

    public QuadPoly(float[] a) throws Exception {
        super(a);
        if (a.length > 3){
            throw new Exception("Not a Quadratic Polynomial");
        }
    }

    public QuadPoly(int degree) throws Exception {
        super(degree);
        if (degree > 2) {
            throw new Exception("Not a Quadratic Polynomial");
        }
    }

    private static boolean isQuadratic(Poly qPoly) {
        qPoly.clean();
        if (qPoly.getDegree() > 2){
            return false;
        } else return true;
    }

    private static QuadPoly copytoQuadPoly(Poly p) throws Exception{
        QuadPoly result = new QuadPoly(p.getDegree());
        for(int i = 0; i < p.getDegree() + 1; i++){
            result.setCoefficient(i, p.getCoefficient(i));
        }
        return result;
    }

    public QuadPoly add(QuadPoly p) throws Exception {
        Poly polyR;
        if (!QuadPoly.isQuadratic(polyR = super.add(p))) {
            throw new Exception("Not a Quadratic Polynomial");
        } else {
            return QuadPoly.copytoQuadPoly(polyR);
        }
    }

    public QuadPoly multiplyPolys(QuadPoly p) throws Exception {
        Poly polyR;
        if (!QuadPoly.isQuadratic(polyR = super.multiplyPolys(p))){
            throw new Exception("Not a Quadratic Polynomial");
        } else {
            return QuadPoly.copytoQuadPoly(polyR);
        }
    }

    public QuadPoly[] factor() throws Exception {
        float a = getCoefficient(2);
        float b = getCoefficient(1);
        float c = getCoefficient(0);
        QuadPoly[] result = new QuadPoly[2];
        
        if(((b*b) - (4*a*c)) < 0) {
            //no real roots
            result[1] = new QuadPoly(new float[] {1});
            result[0] = this;
            return result;
        } else {
            //real roots
            float z = (float)Math.sqrt((b*b)-(4*a*c));
            float[] x, y; //factors
            x = new float[] { (-(-b+z)) , (2*a) };
            y = new float[] { (-(-b-z)) , (2*a) };
            
            System.out.println("x is not before");
            x = QuadPoly.simplify(x);
            System.out.println("after");
            y = QuadPoly.simplify(y);
            result[0] = new QuadPoly(x);
            result[1] = new QuadPoly(y);
            return result;
        }
    }

    private static float[] simplify(float[] a) {
        float min;
        if(a[0] > a[1]) min = a[1];
        else min = a[0];

        for(int i = 2; i < min; i++){
            System.out.println("BAM      "+ a[0]+","+a[1]+ i);
            if(Math.abs(a[0]%i) < 0.00000001 && Math.abs(a[1]%i) < 0.000000001){
                a[0] = a[0] / i;
                a[1] = a[1] / i;
                System.out.println("Zing    " +a[0]+" , "+i+"Zoom    "+ a[1]);
                i = i-1;
            }
        }
        return a;
    }


    public static void main(String[] argv) throws Exception{
        QuadPoly p1 = new QuadPoly(new float[] {-1,0,4});
        QuadPoly p2 = new QuadPoly(new float[] {1,2});
        QuadPoly p3 = new QuadPoly(new float[] {4,6,4});

        p1.add(p2).displayPoly();
        //p1.multiplyPolys(p2).displayPoly();
        QuadPoly[] p4 = p3.factor();
        
        p4[0].displayPoly();
        p4[1].displayPoly();
        float a = -4.0f;
        float b = Math.abs(a % 2);
        System.out.println("test, "+ b);
        QuadPoly[] bam = p1.factor();
        bam[0].displayPoly();
        bam[1].displayPoly();
    }
}
