import java.sql.*;
import java.util.*;

/**
 * The class implements methods of the Sales database
 * interface.
 *
 * All methods of the class receive a Connection object through which all
 * communication to the database should be performed. Note: the
 * Connection object should not be closed by any method.
 *
 * Also, no method should throw any exceptions. In particular, in case
 * that an error occurs in the database, then the method should print an
 * error message and call System.exit(-1);
 */
public class SalesApplication {

    private Connection connection;
    
    /*
     * Constructor
     */
    public SalesApplication(Connection connection) {
        this.connection = connection;
    }
    
    public Connection getConnection()
    {
        return connection;
    }
    
     /**
     * Return list of product names for products whose total sales 
     * i.e. , the total price of the sale of the product across all sales
     * is greater than some specified amount
     * 
     */
    public List<String> getProductNamesWithTotalPriceLargerThan(double amount) {
        List<String> result = new ArrayList<String>();
        // your code here

        
        
        // end of your code
        return result;  
    }

    /**
     * Add a product to the database. If the product’s name and manufacturer
     * already exists in the database, return the product’s id. Otherwise,
     * add the product to the database, and return the new product id.
     * When a new product is added to the database, its category should be NULL.
     *
     * Adding a product and a manufacturer should be done
     * within a transaction. The isolation level should be Serializable.
     *
     * You will lose credit if this is not done in a transaction; you will get extra
     * credit if you do this in a stored procedure.
     */
    public int addProduct(String name, String manufacturer) {
        int productId = 0;
        // your code here
        
        
        

        // end of your code
        return productId;
    }

};
