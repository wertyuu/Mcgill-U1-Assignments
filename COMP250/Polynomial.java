public class Polynomial extends Poly {

    public void MultpyConstant(double value) {
        for(int i = 0; i < coefficients.length; i++) {
            coefficients[i] *= value;
        }
    }
}
