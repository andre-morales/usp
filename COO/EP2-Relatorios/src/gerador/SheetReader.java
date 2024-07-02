package gerador;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

/**
 * @author Andre
 * @version 1.0
 */
public class SheetReader {
	public static Collection<Produto> readFrom(String path) {
		List<Produto> products = new ArrayList<>();
		
		try {
			// Leitor linha a linha
			BufferedReader br = new BufferedReader(new FileReader(path));
			
			// Ignora o cabeçalho
			br.readLine();
			
			String line;
			while ((line = br.readLine()) != null) {
				// Cria um scanner para essa linha
				Scanner scan = new Scanner(line);
				scan.useLocale(Locale.US);
				scan.useDelimiter(", ");
				
				// Lê as propriedades
				int id = scan.nextInt();
				String title = scan.next();
				String category = scan.next();
				int amount = scan.nextInt();
				double price = scan.nextDouble();
				boolean isBold = scan.nextBoolean();
				boolean isItalics = scan.nextBoolean();
				String hexColor = scan.next();
				
				// Instancia o novo produto e o adiciona na lista
				Produto prod = new ProdutoEstilizado(id, title, category, amount, price, isBold, isItalics, hexColor);
				products.add(prod);
			}
		} catch (IOException ex) {
			throw new RuntimeException(ex);
		}
		return products;
	}
}

