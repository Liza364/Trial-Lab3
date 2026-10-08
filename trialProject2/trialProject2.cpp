#include <iostream>
#include <string>
#include <print>
#include <cmath>

// объявили до класса
enum TransportType {
	bus, trolleybus, tram, minibus
};

class Vehicle {
private:
	std::string vehicleNumber;
	TransportType type;
	double fuelPer100km;
	double mileageKm;
	bool isAvailable;
	static double sFuelPrice;
	void validateVehicle() {
		// приватный метод валидации — вызывается из конструктора и сеттеров
		if (vehicleNumber.length() != 8) {
			std::println("Предупреждение: номер должен быть 8 символов. Установлено 'XXXXXXX-0'.");
			vehicleNumber = "XXXXXX-0";
		}
		if (fuelPer100km < 0.0 || fuelPer100km > 100.0) {
			std::println("Предупреждение: расход вне диапазона [0..100]. Установлено 0.");
			fuelPer100km = 0.0;
		}
		if (mileageKm < 0.0 || mileageKm > 1000000.0) {
			std::println("Предупреждение: пробег вне диапазона [0..1 000 000]. Установлено 0.");
			mileageKm = 0.0;
		}
	}

public:

	static double getFuelPrice()
	{
		return sFuelPrice;
	}
	static void setFuelPrice(double price) {
		if (price >= 0) sFuelPrice = price;
	}

	// конструктор перемещения
	Vehicle(Vehicle&& moved) noexcept {
		vehicleNumber = moved.vehicleNumber;
		type = moved.type;
		fuelPer100km = moved.fuelPer100km;
		mileageKm = moved.mileageKm;
		isAvailable = moved.isAvailable;
	}


	// оператор присваивания с перемещением
	Vehicle& operator=(Vehicle&& moved) noexcept{
		vehicleNumber = moved.vehicleNumber;
		type = moved.type;
		fuelPer100km = moved.fuelPer100km;
		mileageKm = moved.mileageKm;
		isAvailable = moved.isAvailable;
	}


	//  оператор присваивания копированием
	Vehicle& operator =(const Vehicle& other) {
		this->vehicleNumber = other.vehicleNumber;
		this->type = other.type;
		this->fuelPer100km = other.fuelPer100km;
		this->mileageKm = other.mileageKm;
		this->isAvailable = other.isAvailable;
	}

	// конструктор с одним параметром
	explicit Vehicle(double mileage) :
		vehicleNumber{ "324472-7" },
		type{ bus },
		fuelPer100km{ 30.0 },
		mileageKm{ mileage },
		isAvailable{ true }
	{
		validateVehicle();

	}

	// конструктор копирования
	Vehicle(const Vehicle& other) :
		vehicleNumber{ other.vehicleNumber },
		type{ other.type },
		fuelPer100km{ other.fuelPer100km },
		mileageKm{ other.mileageKm },
		isAvailable{ other.isAvailable }
	{

	}

	// конструктор по умолчанию
	Vehicle() : vehicleNumber{ "E12345-8" }, type{ bus }, fuelPer100km{ 25.0 }, mileageKm{ 0.0 },
		isAvailable{ true }
	{
		// тут можно писать валидацию, но здесь она не нужна: задан шаблон мной

	}

	Vehicle(std::string number, TransportType transport, double fuel, double mileage, bool available)
		: vehicleNumber{ number }, type{ transport }, fuelPer100km{ fuel }, mileageKm{ mileage }, isAvailable{ available }
	{
		// валидация после списка инициализации
		validateVehicle();
	}

	~Vehicle() {
		std::println("[DESTRUCTOR] транспорт с номером {} уничтожен", vehicleNumber);

	}

	// геттеры
	std::string getVehicleNumber() const {
		return vehicleNumber;
	}
	TransportType getType() const {
		return type;
	}
	double getFuelPer100km() const {
		return fuelPer100km;
	}
	double getMileageKm() const {
		return mileageKm;
	}
	bool getIsAvailable() const {
		return isAvailable;
	}

	// Возвращает тип транспорта как строку
	std::string getTypeAsString() const {
		switch (type) {
		case bus:        return "Автобус";
		case trolleybus: return "Троллейбус";
		case tram:       return "Трамвай";
		case minibus:    return "Маршрутка";
		default:         return "Неизвестно";
		}
	}


	// сеттеры
	void setVehicleNumber(std::string number) {

		vehicleNumber = number;
		validateVehicle();
	}
	void setType(TransportType transport) {
		type = transport;
	}
	void setFuelPer100km(double fuel) {
		fuelPer100km = fuel;
		validateVehicle();
	}
	void setMileageKm(double mileage) {
		mileageKm = mileage;
		validateVehicle();
	}

	void setIsAvailable(bool available) {
		isAvailable = available;
	}


	// методы

	// методы расчета
	double fuelConsumptionCalculation() const {
		return (mileageKm / 100.0) * fuelPer100km;
	}

	// новый метод - расчет стоимости топлива при заданной цене за литр
	double calculateFuelCost() const {
		return round((fuelConsumptionCalculation() * sFuelPrice) * 100.0) / 100.0;
	}

	void printInfo() const {
		std::println( "=================================================");
		std::println( "Номер транспортного средства: {}", vehicleNumber);
		std::println("Тип транспорта: {}", getTypeAsString());
		std::println("Расход топлива на 100 км: {}", fuelPer100km);
		std::println("Пробег (км): {}", mileageKm);
		std::println("Статус доступности: {}", isAvailable ? "Доступен" : "Недоступен");
		std::println("=================================================");
	}

	// методы изменения

	// новый метод - добавить пробег
	void updateMileage(double km) {
		if (km > 0.0 && (mileageKm + km) <= 1000000.0) {
			mileageKm += km;
			std::println("Пробег увеличен на {} км. Текущий пробег: {} км", km, mileageKm);
		}
		else {
			std::println("Ошибка: пробег не может быть отрицательным или превышать 1 000 000 км!");
		}
	}

	void changeAvailableStatus() {
		isAvailable = !isAvailable;
		std::println("Статус изменен. Теперь: {}", isAvailable ? "Доступен" : "Недоступен");
	}
};

class Driver {
private:
	std::string driverName;
	std::string licenseCategory;
	int yearsOfExperience;
public:
	std::string getLicenseCategory() const {
		return licenseCategory;
	}
	void setLicenseCategory(std::string category) {
		if (category == "B" || category == "D" || category == "F" || category == "I") {
			licenseCategory = category;
		}
		else {
			std::println("{}", "Недопустимая или несуществующая категория");
		}
	}
	int getYearsOfExperience() const {
		return yearsOfExperience;
	}
	void setYearsofExperience(int exp) {
		if (exp > 0) {
			yearsOfExperience = exp;
		}
		else {
			std::println( "Опыт не может быть меньше 0");
		}
	}

	void validateDriver() {
		if (licenseCategory != "B" && licenseCategory != "D" && licenseCategory != "F" && licenseCategory != "I") {
			std::println("{}", "Недопустимая или несуществующая категория");
		}
		if (yearsOfExperience < 0) {
			std::println("Опыт не может быть меньше 0");
		}
	}

	Driver() : driverName{"Не указано"}, licenseCategory{"Не указана"}, yearsOfExperience{0}
	{
	
	}

	Driver(std::string name, std::string category, int exp):
	driverName{name}, licenseCategory{category}, yearsOfExperience{exp}
	{
		validateDriver();
	}
};

class Route {
private:
	std::string startStation;
	std::string endStation;
	double lengthKm;
	int averageSpeed;
	double travelTimeHours;
public:
	void setAverageSpeed(int speed) {
		averageSpeed = speed;
	}
	void setStartStation(std::string startSt) {
		startStation = startSt;
	}
	void setEndStation(std::string endSt) {
		endStation = endSt;
	}
	int getAverageSpeed() {
		return averageSpeed;
	}
	std::string getStartStation() {
		return startStation;
	}
	std::string getEndStation() {
		return endStation;
	}
	double checkTravelTime() {
		travelTimeHours = lengthKm / averageSpeed;
	}
	void validateRoute() {

	}

	Route() : startStation{ "Не указана" }, endStation{ "Не указана" },
		lengthKm{0.0}, averageSpeed{0}, travelTimeHours{0.0}
	{

	}

	Route(std::string startSt, std:: string endSt, double length, int speed, double time) : 
		startStation{startSt}, endStation{endSt}, lengthKm{length},
		averageSpeed{speed}, travelTimeHours{time}
	{
		validateRoute();
	}
};

double Vehicle::sFuelPrice = 3.0;

int main() {
	// работа с локальными объектами
	Vehicle vehicle1{};
	Vehicle vehicle2{ 0.00 };
	Vehicle vehicle3{ "244344-7", minibus, 23, 0.00, true };
	Vehicle vehicle4{ vehicle2 };
	vehicle1.setIsAvailable(false);
	vehicle3.setType(bus);
	vehicle3.calculateFuelCost();
	vehicle4.updateMileage(34.55);



	//// создаем локальную область, чтобы наглядно показать работу деструктора
	{
		// работа с локальными массивами объектов
		Vehicle stVehicle1[5]{};
		stVehicle1[0].setFuelPer100km(32.66);
		stVehicle1[4].setMileageKm(20.30);
		Vehicle stVehicle2[3]{
			{"E35552-7", minibus, 23, 0.00, true},{"E66681-7", tram, 36, 0.00, true},
			{"E45281-7", trolleybus, 20, 0.00, false}
		};

		for (const Vehicle& vehicle : stVehicle2) {
			std::println("Стоимость топлива для транспорта из локального массива : {}  руб.", vehicle.calculateFuelCost());
		}

	}

	

	Vehicle* dynVehicle1 = new Vehicle{};
	delete dynVehicle1;
	Vehicle* dynVehicle2 = new Vehicle{ 2500.00 };
	delete dynVehicle2;
	Vehicle* dynVehicle3 = new Vehicle{ "E11111-7", minibus, 19, 100.00, true };
	Vehicle* dynVehicle4 = new Vehicle{ *dynVehicle3 };
	dynVehicle4->calculateFuelCost();
	delete dynVehicle3;
	delete dynVehicle4;

	Vehicle* dynArrVehicle = new Vehicle[4];
	dynArrVehicle[0].setFuelPer100km(30.12);
	dynArrVehicle[2].setVehicleNumber("E22222-07");
	Vehicle* dynArrVehicle1 = new Vehicle[3]{
		{"E3747B-7", bus, 20.5, 20020.41, true},
		{"E6666A-7", bus, 20.5, 20020.41, true},
		{"E3232C-7", bus, 20.5, 20020.41, true}
	};
	dynArrVehicle1->changeAvailableStatus();
	delete[] dynArrVehicle;
	dynArrVehicle = nullptr;
	delete[] dynArrVehicle1;
	dynArrVehicle1 = nullptr;

	std::println("Цена за топливо: {}", Vehicle::getFuelPrice());
	Vehicle::setFuelPrice(2.0);
	std::println("Измененная цена за топливо: {}", Vehicle::getFuelPrice());
	Vehicle anyVehicle{};
	std::println({""}, anyVehicle.getFuelPrice());

	Driver* dynArrDrivers = new Driver[3]{
		{"Alexander", "B", 6},
		{"Anastasia", "F", 12},
		{"Natalia", "D", 4}
	};
	std::println("Стаж второго водителя: {} лет", dynArrDrivers[1].getYearsOfExperience());
	dynArrDrivers[1].setLicenseCategory("D");
	delete[] dynArrDrivers;
	dynArrDrivers = nullptr;

	// Демонстранция работы конструкторов копирования и перемещения
	Vehicle car{"E52345-7", minibus, 21.7, 233.41, true };
	Vehicle car1{ car };
	car1.setMileageKm(0.0);
	Vehicle car2{ car1 };
	std::println("Пробег у car2 теперь {} км", car2.getMileageKm());

	// создание массива
	Vehicle vehicleFleet[6] = {
	Vehicle{"E2363B-7", bus, 20.5, 20020.41, true},
	Vehicle{"E7777A-7", tram, 33.3, 25730.29, false},
	Vehicle{"E5433C-7", minibus, 27.5, 52000.78, true },
	Vehicle{"E5763G-7", trolleybus, 25.9, 12000.15, false},
	Vehicle{"E2533B-7", minibus, 21.4, 20760.63, true},
	Vehicle{"E1111A-7", bus, 23.5, 200.43, true}
	};

	for (const Vehicle& vehicle : vehicleFleet) {
		std::println("Транспорт {} израсходовал {} л", vehicle.getVehicleNumber(), vehicle.fuelConsumptionCalculation());
	};

	for (const Vehicle& vehicle : vehicleFleet) {
		vehicle.printInfo();
	}

	vehicleFleet[0].updateMileage(500.0);
	std::println("Обновление пробега: сейчас он стал {}", vehicleFleet[0].getMileageKm());


	std::println("Затраты на топливо (при цене 3 руб/л) ============");
	for (const Vehicle& vehicle : vehicleFleet) {
		std::println( "Транспорт {}: {} руб", vehicle.getVehicleNumber(), vehicle.calculateFuelCost());
	}
	
	return 0;
}

// Разделить прогу на модули: классы (все в одном модуле), main, методы
// Замечание: если есть сеттер со статусом доступности, зачем сказали делать метод для смены доступности

