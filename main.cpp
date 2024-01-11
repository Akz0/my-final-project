#include "Model.h"
#include "Skybox.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};

std::string CubeMapTextureFaces[6] =
{
	"./textures/skybox/right.png",
	"./textures/skybox/left.png",
	"./textures/skybox/top.png",
	"./textures/skybox/bottom.png",
	"./textures/skybox/front.png",
	"./textures/skybox/back.png"
};

int main() {

	if (!glfwInit()) {
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Project", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK) {
		return -1;
	}


	glEnable(GL_DEPTH_TEST);


	Shader HouseProgram("./shaders/vertex.glsl", "./shaders/normalMap-fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader CastleProgram("./shaders/vertex.glsl", "./shaders/fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader BusProgram("./shaders/vertex.glsl", "./shaders/fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader ZombieProgram1("./shaders/vertex.glsl", "./shaders/fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader ZombieProgram2("./shaders/vertex.glsl", "./shaders/fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader ZombieProgram3("./shaders/vertex.glsl", "./shaders/fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader ZombieProgram4("./shaders/vertex.glsl", "./shaders/fragment.glsl", "./shaders/explode-geometry.glsl");

	Shader lightShader("./shaders/light-vertex.glsl", "./shaders/light-fragment.glsl", "./shaders/explode-geometry.glsl");

	Shader lightShader2("./shaders/light-vertex.glsl", "./shaders/light-fragment.glsl", "./shaders/explode-geometry.glsl");
	Shader floorShaderProgram("./shaders/vertex.glsl", "./shaders/fragment.glsl","./shaders/explode-geometry.glsl");

	Shader SkyboxShaderProgram("./shaders/skybox-vertex.glsl", "./shaders/skybox-fragment.glsl");
	Shader ShadowMapProgram("./shaders/shadow-vertex.glsl", "./shaders/shadow-fragment.glsl");


	std::vector<std::vector<Texture>> FloorTextures
	{
		{Texture("./textures/ground.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)}
	};

	std::vector<std::vector<Texture>> HouseTextures = {
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/house2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
	};

	std::vector<std::vector<Texture>> BusTextures = {
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/bus.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
	};

	std::vector<std::vector<Texture>> FancyCastleTextures = {
		{Texture("./textures/castle/exterior.jpg.", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/castle/door.jpg", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/castle/ground.jpg", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/castle/interior.jpg", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
	};

	Texture HouseNormalMap("./textures/house2_normal.png", "normal", 0, GL_RGB, GL_UNSIGNED_BYTE);
	/*

	std::vector<std::vector<Texture>> FancyCastleTextures = {
		{Texture("./textures/fancy_castle/3.png.", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/fancy_castle/2.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/fancy_castle/1.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
		{Texture("./textures/fancy_castle/0.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
	};
	*/

	std::vector<std::vector<Texture>> ZombieTextures = {
		{Texture("./textures/zombie.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE)},
	};

	

	//Main Light
	//glm::vec4 lightColor = glm::vec4(0.66f, 0.75f, 1.0f, 1.0f);
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPosition = glm::vec3(0.0f, 10.0f, 10.0f);

	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(1.0f, 1.0f, 1.0f)*0.2f);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	Model Light("./models/ball.obj", HouseTextures);
	Light.model = lightModel;

	Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 1.0f, 2.0f));

	

	std::cout << "\nFloor : " << std::endl;
	Model Floor("./models/surface.obj", FloorTextures);
	glm::vec3 floorPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 Floor_model = glm::mat4(1.0f);
	Floor_model = glm::translate(Floor_model, floorPosition);
	Floor_model = glm::scale(Floor_model, glm::vec3(1.0f, 1.0f, 1.0f) * 2000.0f);
	Floor.model = Floor_model;
	Floor.UpdateLight(floorShaderProgram, lightColor, lightPosition);
	
	std::cout << "\nHouse : " << std::endl;
	Model House("./models/house2.obj", HouseTextures);
	glm::vec3 HousePosition = glm::vec3(-10.0f, 0.0f, 5.0f);
	glm::mat4 House_model= glm::mat4(1.0f);
	House_model = glm::translate(House_model, HousePosition);
	House_model = glm::scale(House_model, glm::vec3(1.0f, 1.0f, 1.0f) * 3.0f);
	House_model = glm::rotate(House_model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	House.model = House_model;
	House.UpdateLight(HouseProgram,lightColor,lightPosition);
	
	std::cout << "\nCastle : " << std::endl;
	Model Castle("./models/castle.obj", FancyCastleTextures);
	glm::vec3 CastlePosition = glm::vec3(2.0f, 0.0f, 3.0f);
	glm::mat4 Castle_model = glm::mat4(1.0f);
	Castle_model = glm::translate(Castle_model, CastlePosition);
	Castle_model = glm::scale(Castle_model, glm::vec3(1.0f, 1.0f, 1.0f) * 200.0f );
	Castle.model = Castle_model;
	Castle.UpdateLight(CastleProgram, lightColor, lightPosition);

	std::cout << "\Bus : " << std::endl;
	Model Bus("./models/bus.obj", BusTextures);
	glm::vec3 BusPosition = glm::vec3(25.0f, 3.5f, 2.0f);
	glm::mat4 Bus_model = glm::mat4(1.0f);
	Bus_model = glm::translate(Bus_model, BusPosition);
	Bus_model = glm::scale(Bus_model, glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f);
	Bus_model = glm::rotate(Bus_model,glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Bus.model = Bus_model;
	Bus.UpdateLight(BusProgram, lightColor, lightPosition);


	// Zombies
	std::cout << "\nZombie 1: " << std::endl;
	Model Zombie1("./models/zombie.obj", ZombieTextures);
	glm::vec3 ZombiePosition1 = glm::vec3(0.0f, 0.8f, 0.0f);
	glm::mat4 Zomebie_model1 = glm::mat4(1.0f);
	Zomebie_model1 = glm::translate(Zomebie_model1, ZombiePosition1);
	Zomebie_model1 = glm::scale(Zomebie_model1, glm::vec3(1.0f, 1.0f, 1.0f) * 3.0f);
	Zomebie_model1 = glm::rotate(Zomebie_model1, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Zombie1.model = Zomebie_model1;
	Zombie1.UpdateLight(ZombieProgram1, lightColor, lightPosition);

	std::cout << "\nZombie 2: " << std::endl;
	Model Zombie2("./models/zombie.obj", ZombieTextures);
	glm::vec3 ZombiePosition2 = glm::vec3(2.0f, 0.8f, 4.0f);
	glm::mat4 Zomebie_model2 = glm::mat4(1.0f);
	Zomebie_model2 = glm::translate(Zomebie_model2, ZombiePosition2);
	Zomebie_model2 = glm::scale(Zomebie_model2, glm::vec3(1.0f, 1.0f, 1.0f) * 3.0f);
	Zomebie_model2 = glm::rotate(Zomebie_model2, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Zombie2.model = Zomebie_model2;
	Zombie2.UpdateLight(ZombieProgram2, lightColor, lightPosition);


	std::cout << "\nZombie 3: " << std::endl;
	Model Zombie3("./models/zombie.obj", ZombieTextures);
	glm::vec3 ZombiePosition3 = glm::vec3(1.0f, 0.8f, 9.0f);
	glm::mat4 Zomebie_model3 = glm::mat4(1.0f);
	Zomebie_model3 = glm::translate(Zomebie_model3, ZombiePosition3);
	Zomebie_model3 = glm::scale(Zomebie_model3, glm::vec3(1.0f, 1.0f, 1.0f) * 3.0f);
	Zomebie_model3 = glm::rotate(Zomebie_model3, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Zombie3.model = Zomebie_model3;
	Zombie3.UpdateLight(ZombieProgram3, lightColor, lightPosition);


	std::cout << "\nZombie 4: " << std::endl;
	Model Zombie4("./models/zombie.obj", ZombieTextures);
	glm::vec3 ZombiePosition4 = glm::vec3(5.0f, 0.8f, 13.0f);
	glm::mat4 Zomebie_model4 = glm::mat4(1.0f);
	Zomebie_model4 = glm::translate(Zomebie_model4, ZombiePosition4);
	Zomebie_model4 = glm::scale(Zomebie_model4, glm::vec3(1.0f, 1.0f, 1.0f) * 3.0f);
	Zomebie_model4 = glm::rotate(Zomebie_model4, glm::radians(190.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Zombie4.model = Zomebie_model4;
	Zombie4.UpdateLight(ZombieProgram4, lightColor, lightPosition);
	
	

	// Skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	unsigned int CubeMapTexture;
	glGenTextures(1, &CubeMapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//Completed Skybox


	//Shadow Map
	// Framebuffer for Shadow Map
	unsigned int shadowMapFBO;
	glGenFramebuffers(1, &shadowMapFBO);

	unsigned int shadowMapWidth = 2048, shadowMapHeight = 2048;
	unsigned int shadowMap;
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float farPlane = 1000.0f;
	glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, farPlane);
	glm::mat4 PerspectiveProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, farPlane);
	glm::mat4 lightView = glm::lookAt(20.0f * lightPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 lightProjection = PerspectiveProjection * lightView;

	ShadowMapProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(ShadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));



	//Complete ShadowMap


	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, numberOfChannels;
		unsigned char* data = stbi_load(CubeMapTextureFaces[i].c_str(), &width, &height, &numberOfChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
			std::cout << " Loaded Texture For Skybox : " << CubeMapTextureFaces[i].c_str() << std::endl;
		}
		else
		{
			std::cout << "Failed to load texture: " << CubeMapTextureFaces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	static float XChange = 0.0f;
	static float ZChange = 0.005f;
	static float T = 0;
	static float M = 0;
	static float speed = 0.001f;

    while (!glfwWindowShouldClose(window)) {
		
		//Shadow Frame Buffer
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//Shadow Frame Buffer End

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 1000.0f);
		
		// Send the light matrix to the shader
		HouseProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(HouseProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(HouseProgram.ID, "T"),T);

		M += speed;
		BusProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(BusProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(BusProgram.ID, "T"),M);

		CastleProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(CastleProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(CastleProgram.ID, "T"), T);

		ZombieProgram1.Activate();
		glUniformMatrix4fv(glGetUniformLocation(ZombieProgram1.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(ZombieProgram1.ID, "T"), T);

		ZombieProgram2.Activate();
		glUniformMatrix4fv(glGetUniformLocation(ZombieProgram2.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(ZombieProgram2.ID, "T"), T);

		ZombieProgram3.Activate();
		glUniformMatrix4fv(glGetUniformLocation(ZombieProgram3.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(ZombieProgram3.ID, "T"), T);

		ZombieProgram4.Activate();
		glUniformMatrix4fv(glGetUniformLocation(ZombieProgram4.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
		glUniform1f(glGetUniformLocation(ZombieProgram4.ID, "T"), T);

		// Bind the Shadow Map
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glUniform1i(glGetUniformLocation(HouseProgram.ID, "shadowMap"), 2);
		//

		House.UpdateCamera(HouseProgram, camera);
		Floor.UpdateCamera(floorShaderProgram, camera);
		Castle.UpdateCamera(CastleProgram, camera);
		Bus.UpdateCamera(BusProgram, camera);


		Zombie1.model =  glm::translate(Zombie1.model, glm::vec3(XChange, 0, ZChange));
		Zombie1.UpdateCamera(ZombieProgram1, camera);

		Zombie2.model = glm::translate(Zombie2.model, glm::vec3(XChange, 0, ZChange));
		Zombie2.UpdateCamera(ZombieProgram2, camera);

		Zombie3.model = glm::translate(Zombie3.model, glm::vec3(XChange, 0, ZChange));
		Zombie3.UpdateCamera(ZombieProgram3, camera);

		Zombie4.model = glm::translate(Zombie4.model, glm::vec3(XChange, 0, ZChange));
		Zombie4.UpdateCamera(ZombieProgram4, camera);


		lightShader.Activate();
		camera.Matrix(lightShader, "CameraMatrix");

		HouseNormalMap.Bind();
		HouseNormalMap.texUnit(HouseProgram, "normal0", 1);

		House.Draw(HouseProgram,camera);
		Floor.Draw(floorShaderProgram, camera);
		Castle.Draw(CastleProgram, camera);
		Bus.Draw(BusProgram, camera);

		Zombie1.Draw(ZombieProgram1, camera);
		Zombie2.Draw(ZombieProgram2, camera);
		Zombie3.Draw(ZombieProgram3, camera);
		Zombie4.Draw(ZombieProgram4, camera);

		Light.Draw(lightShader, camera);


		//Skybox
		glDepthFunc(GL_LEQUAL);
		SkyboxShaderProgram.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(SkyboxShaderProgram.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyboxShaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		//Skybox End

		glfwSwapBuffers(window);
		glfwPollEvents();
    }

	HouseProgram.Delete();
	lightShader.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

