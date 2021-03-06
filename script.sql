USE [master]
GO
/****** Object:  Database [pmdb]    Script Date: 7/5/2022 12:41:55 AM ******/
CREATE DATABASE [pmdb]
USE [pmdb]
GO
/****** Object:  Table [dbo].[Teams]    Script Date: 7/5/2022 12:41:55 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Teams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](50) NOT NULL,
	[DateOfCreation] [datetime2](7) NOT NULL,
	[IdOfCreator] [int] NOT NULL,
	[DateOfLastChange] [datetime2](7) NOT NULL,
	[IdOfLastChanger] [int] NOT NULL,
 CONSTRAINT [PK_Teams] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UQ_Teams_Name] UNIQUE NONCLUSTERED 
(
	[Name] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 7/5/2022 12:41:55 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Username] [nvarchar](50) NOT NULL,
	[Password] [nvarchar](255) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[LastName] [nvarchar](50) NOT NULL,
	[DateOfCreation] [datetime2](7) NOT NULL,
	[IdOfCreator] [int] NOT NULL,
	[DateOfLastChange] [datetime2](7) NOT NULL,
	[IdOfLastChanger] [int] NOT NULL,
	[IsDeleted] [bit] NOT NULL,
	[IsAdmin] [bit] NOT NULL,
 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY],
 CONSTRAINT [UQ_User_Username] UNIQUE NONCLUSTERED 
(
	[Username] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/5/2022 12:41:55 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UsersTeams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[UserId] [int] NOT NULL,
	[TeamId] [int] NOT NULL,
 CONSTRAINT [PK_UsersTeams] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_DateOfCreation]  DEFAULT (getdate()) FOR [DateOfCreation]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_IsDeleted]  DEFAULT ((0)) FOR [IsDeleted]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users1] FOREIGN KEY([IdOfLastChanger])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users1]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Id_Users_IdOfCreator] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Id_Users_IdOfCreator]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_Id_Users_IdOfLastChanger] FOREIGN KEY([IdOfLastChanger])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_Id_Users_IdOfLastChanger]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Teams] FOREIGN KEY([TeamId])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Teams]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Users] FOREIGN KEY([UserId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Users]
GO
/****** Object:  Trigger [dbo].[OnTeamDelete]    Script Date: 7/5/2022 12:41:55 AM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER [dbo].[OnTeamDelete] 
ON [dbo].[Teams] 
INSTEAD OF DELETE AS BEGIN
	DECLARE @id INT;
	SELECT @id = Id FROM DELETED;

	DELETE FROM UsersTeams
	WHERE UsersTeams.TeamId = @id;

	DELETE FROM Teams
	WHERE Id = @id;
END
GO
ALTER TABLE [dbo].[Teams] ENABLE TRIGGER [OnTeamDelete]
GO
USE [master]
GO
ALTER DATABASE [pmdb] SET  READ_WRITE 
GO
