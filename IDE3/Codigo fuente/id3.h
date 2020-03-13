
void id3(tabla& principal) {

	if(!principal.getEsTablaFinal()) {

		principal.resolverTabla();

		for(tabla& subTabla : principal.getSubTablas())

			subTabla.mostrarAtributosDatos();

	}

}

void id3(tabla& principal, std::vector<std::string>& reglasInferidas) {

	if(!principal.getEsTablaFinal()) {

		principal.resolverTabla();

		for(tabla& subTabla : principal.getSubTablas()) {

			subTabla.mostrarAtributosDatos();

			id3(subTabla,reglasInferidas);

		}

	} else

		reglasInferidas.push_back(principal.getNombre());

}
