/*
*Proyecto realizado por:
*Daniel Fierro
*Juan Esteban Rincon
*Marco Valencia
*/

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        JSONParser parser = new JSONParser();
        Scanner sc = new Scanner(System.in);
        Operaciones op = new Operaciones();
        int  numero_parametros, numero_nodos;
        Premisa premisa_de_entrada;
        ArrayList<Premisa> consulta = new ArrayList<>();
        ArrayList<Datos> nodos = new ArrayList<>();
        llenarLista(nodos);
        for(Datos dt: nodos){
            System.out.println(dt.getPremisa());
        }
        try{
            Object obj = parser.parse(new FileReader("tablas2.json"));
            JSONObject jsonObject = (JSONObject) obj;
            System.out.println(jsonObject);
            //System.out.println("leido"+jsonObject.get("A"));

            JSONArray array = (JSONArray) jsonObject.get("A");
           /* for(int i =0; i<array.size();i++){
                JSONObject jsonObject1 = (JSONObject) array.get(i);
                System.out.println("T: "+jsonObject1.get("T"));
                System.out.println("attend: "+jsonObject1.get("attend"));
                System.out.println("miss: "+jsonObject1.get("miss"));
            }*/

            System.out.println("Inferencia por enumeracion");
            System.out.println("Ingrese el numero de parametros de la consulta:");
            numero_parametros = sc.nextInt();
            sc.nextLine();
            for(int i = 0; i<numero_parametros; i++){
                premisa_de_entrada = new Premisa();
                System.out.println("Ingrese nombre del parametro:");
                premisa_de_entrada.setNombre(sc.nextLine());
                System.out.println("Ingrese valor del parametro");
                premisa_de_entrada.setValor(sc.nextLine());
                consulta.add(premisa_de_entrada);
            }
            op.compararListas(nodos,consulta);

           for(Premisa p: consulta){
                System.out.println("Nombre:"+p.getNombre());
                System.out.println("Valor:"+p.getValor());
            }
            ArrayList<Double> res = op.calcularSumatoria(nodos,consulta,jsonObject);
           for(Double d: res){
               System.out.print(d+" ");
           }

        }catch (FileNotFoundException e){}
        catch (IOException e){}
        catch (ParseException e){}
    }
    private static void llenarLista(ArrayList<Datos> nodos){
       Datos dato = new Datos();
       dato.setPremisa("R");
       dato.getEvidencias().add("none");
       dato.getEvidencias().add("light");
       dato.getEvidencias().add("heavy");
        nodos.add(dato);
        Datos dato2 = new Datos();
        dato2.setPremisa("M");
        dato2.getEvidencias().add("yes");
        dato2.getEvidencias().add("no");
        nodos.add(dato2);
        /*Datos dato3 = new Datos();
        dato3.setPremisa("T");
        dato3.getEvidencias().add("on time");
        dato3.getEvidencias().add("delayed");
        nodos.add(dato3);
        Datos dato4 = new Datos();
        dato4.setPremisa("A");
        dato4.getEvidencias().add("attend");
        dato4.getEvidencias().add("miss");
        dato4.getEvidencias().clear();
        nodos.add(dato4);*/

    }

}
