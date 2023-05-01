# TaskQueue

## Introduction
Tasks refer to work that may take a long time to complete and can be processed asynchronously. Waiting until a task completes before proceeding with the game is not feasible. To manage these tasks effectively, a Task Queue is utilized, where all the tasks are added and executed in the background. There are two types of Task Queues available: Push Queues and Pull Queues. Push Queues automatically handle the actions that are added to them, whereas Pull Queues contain a list of actions that can be executed at any time.

For instance, Push Queues are useful in messaging systems such as WhatsApp. One can continue to send messages even if the previously sent messages have not been delivered yet. In video games, Push Queues are often used to handle events that happen in real time. For example, in a racing game, events that occur on the track, such as the collision of two cars, can be automatically added to a background task queue to be processed in the order they occurred.

On the other hand, Pull Queues are typically used in RPG games where a character is assigned tasks, and the game processes them in a sequential order. For example, in a real-time strategy game, the player may give specific orders to a group of units, and these orders are added to a task queue that is executed in the order they were received.

## Task Queue in videogames
A great way to learn how to use task queues in video games is by observing how other games have implemented them. Here are some examples of task queues that are easy to identify at first glance.

### Minecraft
In many games with crafting mechanics, players can add crafting recipes to a task queue. The game will then automatically process these recipes, allowing players to continue exploring or engaging in other activities while their items are crafted in the background.

### World of Warcraft
In games with RPG mechanics, players can use powerful abilities that have a cooldown period before they can be used again. These abilities are added to a task queue and cannot be used again until the cooldown has completed.

### Overwatch
In online multiplayer games, the game uses task queues to synchronize gameplay events between players. For example, when a player fires a weapon, the game will add this event to a task queue and broadcast it to other players, ensuring that all players see the same events in the same order.
