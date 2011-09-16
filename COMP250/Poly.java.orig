
public class Poly {

	private float[] coefficients;


	public Poly() {
		coefficients = new float[1];
		coefficients[0] = 0;
	}
	
	public Poly(int degree) {
		coefficients = new float[degree+1];
		for (int i = 0; i <= degree; i++)
			coefficients[i] = 0;
	}
	
	
	public Poly(float[] a) {
		coefficients = new float[a.length];
		for (int i = 0; i < a.length; i++)
			coefficients[i] = a[i];
	}
	
	public int getDegree() {
		return coefficients.length-1;
	}
	
	public float getCoefficient(int i) {
		return coefficients[i];
	}
	
	public void setCoefficient(int i, float value) {
		coefficients[i] = value;
	}
	
	public Poly add(Poly p) {
		int n = getDegree();
		int m = p.getDegree();
		Poly result = new Poly(Poly.max(n, m));
		int i;

			for (i = 0; i <= Poly.min(n, m); i++) 
				result.setCoefficient(i, coefficients[i] + p.getCoefficient(i));
			if (i <= n) {
				//we have to copy the remaining coefficients from this object
				for ( ; i <= n; i++) 
					result.setCoefficient(i, coefficients[i]);
			} else {
				// we have to copy the remaining coefficients from p
				for ( ; i <= m; i++) 
					result.setCoefficient(i, p.getCoefficient(i));
			}
		return result;
	}

        public Poly multiply(double multiplier) {
        
        }

        public Poly multiplyPolys(Poly mult) {
           int n = getDegree();
           int m = mult.getDegree();
           Poly result = new Poly(m+n);

            for (int i = 0; i < (getDegree() + 1); i++) {
                Poly result2 = new Poly(i + mult.getDegree());
                for (int j = 0; j < (mult.getDegree() + 1); j++) {
                    result2.setCoefficient((i + j), (getCoefficient(i) * mult.getCoefficient(j)));
                }
                result = result.add(result2);
            }

            return result;
        }
	
	public void displayPoly () {
		for (int i=0; i < coefficients.length; i++)
			System.out.print(" "+coefficients[i]);
		System.out.println();
	}
	
	private static int max (int n, int m) {
		if (n > m)
			return n;
		return m;
	}
		
	private static int min (int n, int m) {
		if (n > m)
			return m;
		return n;
	}

	
}
