import java.util.ArrayList;

public class Datos {
    private String premisa;
    ArrayList<String> evidencias = new ArrayList<>();

    public Datos() {
    }

    public Datos(String premisa, ArrayList<String> evidencias) {
        this.premisa = premisa;
        this.evidencias = evidencias;
    }

    public String getPremisa() {
        return premisa;
    }

    public void setPremisa(String premisa) {
        this.premisa = premisa;
    }

    public ArrayList<String> getEvidencias() {
        return evidencias;
    }

    public void setEvidencias(ArrayList<String> evidencias) {
        this.evidencias = evidencias;
    }
}
