#include "sistema.h"
#include <iostream>

int main() {
    // Initialize the system
    Sistema sistema;

    // Create Veterinarios
    Veterinario vet1("Dr. João", "CRM12345");
    Veterinario vet2("Dra. Maria", "CRM67890");
    sistema.cadastrarVeterinario(vet1);
    sistema.cadastrarVeterinario(vet2);

    // Create Tutores
    Tutor tutor1("Ana Silva", "12345678901", "11999999999", "Rua A, 123");
    Tutor tutor2("Carlos Santos", "09876543210", "11988888888", "Rua B, 456");

    // Create Animals and link to Tutores
    Animal pet1("Rex", 5, "Golden Retriever", "Nenhum");
    Animal pet2("Mia", 2, "Siamês", "Vacinação completa");

    tutor1.adicionarAnimal(pet1);
    tutor2.adicionarAnimal(pet2);

    sistema.cadastrarTutor(tutor1);
    sistema.cadastrarTutor(tutor2);

    // Schedule Consultations
    Consulta consulta1("2025-01-20", "10:00", "Check-up", vet1.getNome(), &pet1, "Agendada");
    Consulta consulta2("2025-01-20", "15:00", "Vacinação", vet2.getNome(), &pet2, "Agendada");

    sistema.agendarConsulta(consulta1);
    sistema.agendarConsulta(consulta2);

    // Example: Retrieve appointments by date
    std::cout << "Consultas para 2025-01-20:\n";
    auto consultasPorData = sistema.filtrarConsultasPorData("2025-01-20");
    for (const auto& consulta : consultasPorData) {
        std::cout << " - Animal: " << consulta.getAnimal()->getNome()
        << ", Veterinário: " << consulta.getVeterinario()
        << ", Horário: " << consulta.getHorario() << '\n';
    }

    // Example: Display available times for vet1
    std::cout << "\nHorários livres para " << vet1.getNome() << " em 2025-01-20:\n";
    auto horariosLivres = sistema.obterHorariosLivres(vet1, "2025-01-20");
    for (const auto& horario : horariosLivres) {
        std::cout << " - " << horario << '\n';
    }

    return 0;
}
