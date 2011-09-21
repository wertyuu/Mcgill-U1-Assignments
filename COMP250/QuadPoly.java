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

    public QuadPoly multiplyConstant2(float a) throws Exception {
        Poly polyR;
        if (!QuadPoly.isQuadratic(polyR = super.multiplyConstant(a))) {
            throw new Exception("Not a Quadratic Polynomial");
        } else {
            return QuadPoly.copytoQuadPoly(polyR);
        }
    }

    public QuadPoly[] factor() throws Exception {
        float a = 1;
        float a_factored = getCoefficient(2);
        float b = getCoefficient(1) / getCoefficient(2);
        float c = getCoefficient(0) / getCoefficient(2);
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
            
            result[0] = new QuadPoly(x).multiplyConstant2(a_factored);
            result[1] = new QuadPoly(y);
            return result;
        }
    }


    public static void main(String[] argv) throws Exception{
        QuadPoly p1 = new QuadPoly(new float[] {-2,1,6});
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
