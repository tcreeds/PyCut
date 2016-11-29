import pygame
from . import SceneBase
from game.objects import Text, Button, STATE

class DifficultyScene(SceneBase):
    def __init__(self, context):
        SceneBase.__init__(self, context)
        self.createTitle()
        self.createEasyButton()
        self.createAdvancedButton()

    def ProcessInput(self, events, pressed_keys):
        for event in events:
            if event.type == pygame.KEYDOWN and event.key == pygame.K_RETURN:
                # Move to the next scene when the user pressed Enter
                pass

            if event.type == pygame.MOUSEBUTTONDOWN:
                self.easy_button.isClicked(event)
                self.adv_button.isClicked(event)

            if event.type == pygame.MOUSEBUTTONUP:
                self.easy_button.isClicked(event)
                self.adv_button.isClicked(event)

            if event.type == pygame.MOUSEMOTION:
                self.easy_button.isHovered(event)
                self.adv_button.isHovered(event)

    def Update(self):
        pass

    def Render(self):
        # For the sake of brevity, the title scene is a blank red screen
        self.screen.fill((255, 255, 255))
        self.title.drawOn(self.screen)
        self.easy_button.drawOn(self.screen)
        self.adv_button.drawOn(self.screen)

    def createTitle(self):
        self.title = Text(self.context, "Choose Difficulty")
        self.title.setColor((244, 101, 36))
        self.title.setPen(self.context.bold_font_large)
        self.title.setLocation( (self.context.width - self.title.width) // 2,
                                (self.context.height - self.title.height) // 2)

    def createEasyButton(self):
        self.easy_button = Button(self.context, "Easy")
        self.easy_button.setPen(self.context.font_small)
        self.easy_button.setPen(self.context.font, STATE.HOVER)
        self.easy_button.setOnLeftClick(self.handleEasyButtonClick)
        self.easy_button.setBackgroundImg(self.context.button_bg, STATE.NORMAL)
        self.easy_button.setBackgroundImg(self.context.button_bg_active, STATE.ACTIVE)
        self.easy_button.setLocation((self.context.width - self.easy_button.width) // 2,
                                      ((self.context.height - self.easy_button.height) // 2) + self.title.height )

    def createAdvancedButton(self):
        self.adv_button = Button(self.context, "Advanced")
        self.adv_button.setPen(self.context.font_small)
        self.adv_button.setPen(self.context.font, STATE.HOVER)
        self.adv_button.setOnLeftClick(self.handleAdvancedButtonClick)
        self.adv_button.setBackgroundImg(self.context.button_bg, STATE.NORMAL)
        self.adv_button.setBackgroundImg(self.context.button_bg_active, STATE.ACTIVE)
        self.adv_button.setLocation((self.context.width - self.adv_button.width) // 2,
                                      ((self.context.height - self.adv_button.height) // 2) + self.title.height + self.easy_button.height + 5 )

    """
    helper methods below this point
    """

    def handleEasyButtonClick(self):
        self.context.difficulty = "Easy"
        self.SwitchToScene(self.context.starting_scene)

    def handleAdvancedButtonClick(self):
        self.context.difficulty = "Advanced"
        self.SwitchToScene(self.context.starting_scene)
