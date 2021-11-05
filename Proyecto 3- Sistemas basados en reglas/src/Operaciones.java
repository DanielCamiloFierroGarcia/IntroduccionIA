import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.util.ArrayList;

public class Operaciones {
    public Operaciones() {
    }

    public void compararListas(ArrayList<Datos> nodos, ArrayList<Premisa> consulta){
        boolean esta  = false;
        for( Datos dato: nodos){
            for(Premisa pr: consulta){
                if(dato.getPremisa().equals(pr.getNombre())){
                    esta = true;
                }
            }
            if(esta == false){
                Premisa praux = new Premisa();
                praux.setNombre(dato.getPremisa());
                praux.setValor("-");
                consulta.add(praux);
            }
            esta  = false;
        }
    }
    public ArrayList<Double> calcularSumatoria(ArrayList<Datos> nodos, ArrayList<Premisa> consulta, JSONObject OBJ){
        int numero_terminos;
        ArrayList<Double> res = new ArrayList<Double>();

        for(Premisa prem: consulta){
            if(prem.getValor().equals("-")){
                for(Datos dt: nodos){
                    if(prem.getNombre().equals(dt.getPremisa())){
                        for(String evidencia: dt.getEvidencias()){
                            Premisa p = new Premisa(prem.getNombre(),evidencia);
                            System.out.println("nombre: "+p.getNombre());
                            System.out.println("valor: "+p.getValor());
                            res.add(calcularTermino(nodos,consulta,p,OBJ));
                        }
                    }
                }
            }
        }
        return  res;

    }
    public  double calcularTermino(ArrayList<Datos> nodos,ArrayList<Premisa> consulta,Premisa valor_posible,JSONObject OBJ){
        double termino = 0;
        Premisa paux = new Premisa();
        boolean encontro = false;
        for(Premisa p : consulta){
            if(!p.getValor().equals("-")){
                JSONArray arr = (JSONArray) OBJ.get(p.getNombre());
                for(int i = 0; i<arr.size(); i++){
                    JSONObject obj2 = (JSONObject) arr.get(i);
                    for(Datos d: nodos){
                        if(obj2.get(d.getPremisa()) != null){

                            //paux = traerdato(consulta,d.getPremisa());//premisa de dato del cual nse depende si lo encuentra
                            encontro =true;
                            System.out.println("holii");
                        }
                    }
                }
                /////
                if(encontro){
                    for(int i = 0; i<arr.size(); i++){
                        JSONObject obj2 = (JSONObject) arr.get(i);
                        System.out.println();
                        String valor = (String) obj2.get(valor_posible.getNombre());
                        if(obj2.get(p.getValor())!= null && valor.equals(valor_posible.getValor())){
                            System.out.println("aqui toy");
                            String term =obj2.get(p.getValor()).toString();
                            double t = Double.parseDouble(term);
                            System.out.println(t);
                            if(termino!= 0) {
                                termino = termino * t;
                            }
                            else {termino = t;}
                        }
                    }
                }else{
                    for(int i = 0; i<arr.size(); i++){
                        JSONObject obj2 = (JSONObject) arr.get(i);
                        if(obj2.get(p.getValor())!= null){
                            System.out.println("holi");
                            System.out.println(obj2.get(p.getValor()));
                            String term =obj2.get(p.getValor()).toString();
                            double t = Double.parseDouble(term);
                            System.out.println(t);
                            if(termino!= 0) {
                                termino = termino * t;
                            }
                            else {termino = t;}
                        }
                    }
                }
                encontro = false;
            }
        }
        return termino;
    }
    public Premisa traerdato(ArrayList<Premisa> consulta, String key){
        for(Premisa p : consulta){
            if (p.getNombre().equals(key)){
                return p;
            }
        }
        return null;
    }
}
