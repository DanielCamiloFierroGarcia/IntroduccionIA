import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        JSONParser parser = new JSONParser();


        try{
            Object obj = parser.parse(new FileReader("tablas.json"));
            JSONObject jsonObject = (JSONObject) obj;
            System.out.println("leido"+jsonObject.get("A"));

            JSONArray array = (JSONArray) jsonObject.get("A");
            for(int i =0; i<array.size();i++){
                JSONObject jsonObject1 = (JSONObject) array.get(i);
                System.out.println("T: "+jsonObject1.get("T"));
                System.out.println("attend: "+jsonObject1.get("attend"));
                System.out.println("miss: "+jsonObject1.get("miss"));
            }

        }catch (FileNotFoundException e){}
        catch (IOException e){}
        catch (ParseException e){}
    }
}
